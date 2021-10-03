set(minitrace_sources
	# All source files
	"${CMAKE_CURRENT_LIST_DIR}/minitrace.c"

	# All header files(for safety)
	"${CMAKE_CURRENT_LIST_DIR}/include/minitrace/minitrace.h"
	PARENT_SCOPE
)

#option(MTR_BUILD_TEST "Build test apps" OFF)
#if(MTR_BUILD_TEST)
#    add_executable(minitrace_test minitrace_test.cpp)
#    target_link_libraries(minitrace_test ${PROJECT_NAME})
#
#   find_package(Threads)
#    add_executable(minitrace_test_mt minitrace_test_mt.cpp)
#   target_link_libraries(minitrace_test_mt ${PROJECT_NAME} Threads::Threads)
#endif()