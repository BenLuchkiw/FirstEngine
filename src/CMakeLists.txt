set(src_combined_sources 
	# All definition header files(for safety and clarity)
	"${CMAKE_CURRENT_LIST_DIR}/Core/EntryPoint.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/Core/FirstEngine.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanRenderer.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanValidationLayers.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanWindow.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanShader.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanPipeline.hpp"

	# All single header files
	"${CMAKE_CURRENT_LIST_DIR}/Core/FirstEngineInclude.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/Core/Macros.hpp"

	# All source files
	"${CMAKE_CURRENT_LIST_DIR}/Core/EntryPoint.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Core/FirstEngine.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanRenderer.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanValidationLayers.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanWindow.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/GraphicsCore/VulkanCore/VulkanPipeline.cpp"


	PARENT_SCOPE
)