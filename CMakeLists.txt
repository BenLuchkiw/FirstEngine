cmake_minimum_required(VERSION 3.20)

project(FirstEngine
VERSION 1.0
LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Listing all relevant subdirectories
add_subdirectory(src)
add_subdirectory(libs)

# All source files to be compiled into executable
set(all_source_files
	${libs_combined_sources}
	${src_combined_sources}
)

# Creating executable with the empty EntryPoint.cpp file, it links EntryPoint.hpp automatically
# it's an annoying bug(maybe...) and an empty file was the workaround
add_executable(${PROJECT_NAME} ${all_source_files})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Links the main library to the executable
target_link_libraries(${PROJECT_NAME}
	PUBLIC
	# Libs subdirectory libraries
    ${CMAKE_CURRENT_LIST_DIR}/libs/GLFW/lib-vc2019/glfw3.lib
    ${CMAKE_CURRENT_LIST_DIR}/libs/vulkan/Lib/vulkan-1.lib
  )

target_include_directories(${PROJECT_NAME}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/src
	${CMAKE_CURRENT_LIST_DIR}/libs/GLFW/include
	${CMAKE_CURRENT_LIST_DIR}/libs/imgui/include
	${CMAKE_CURRENT_LIST_DIR}/libs/minitrace/include
	${CMAKE_CURRENT_LIST_DIR}/libs/vulkan/include
)
target_compile_definitions(${PROJECT_NAME} PUBLIC ROOT_DIR="${CMAKE_CURRENT_LIST_DIR}")

# TODO make these optional and toggleable
# target_compile_definitions(${PROJECT_NAME} PUBLIC MTR_ENABLED)
target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG)

# Need more stable Vulkan related definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC RENDER_API=1) # 1 means Vulkan and is the only supported API
target_compile_definitions(${PROJECT_NAME} PUBLIC VULKAN_VALIDATION_LAYERS=1)
