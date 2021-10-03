# All desired subdirectories
add_subdirectory(GLFW)
add_subdirectory(imgui)
add_subdirectory(minitrace)
add_subdirectory(vulkan)

set(libs_combined_sources 
	${GLFW_sources}
	${imgui_sources}
	${minitrace_sources}
	${vulkan_sources}
	PARENT_SCOPE
)