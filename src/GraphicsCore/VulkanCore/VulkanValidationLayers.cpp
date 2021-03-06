#include "VulkanValidationLayers.hpp"

namespace FE
{
	bool initValidationLayers()
	{
		FE_SCOPE_TRACE("Startup", "FE::initValidationLayers()");

#if !VULKAN_VALIDATION_LAYERS
		return false;
#endif
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		bool layerFound = false;
		for (const auto& layerProperties : availableLayers) {
			if (strcmp("VK_LAYER_KHRONOS_validation", layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		FE_LOG_WARNING(!layerFound, "Failed to create Vulkan validation layers!")
		return layerFound;

	}

	std::vector<const char*> getRequiredExtensions()
	{
		FE_SCOPE_TRACE("Startup", "FE::getRequiredExtensions()");

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (VULKAN_VALIDATION_LAYERS) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		FE_SCOPE_TRACE("Startup", "FE::debugCallback");

		FE_LOG_INFO(VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT == messageSeverity, pCallbackData->pMessage);
		FE_LOG_WARNING(VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT == messageSeverity, pCallbackData->pMessage);
		FE_LOG_ERROR(VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT == messageSeverity, pCallbackData->pMessage);


		return VK_FALSE;
	}

	void initializeDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT* debugMessenger)
	{
#if !VULKAN_VALIDATION_LAYERS
		return;
#endif
		FE_SCOPE_TRACE("Startup", "FE::initializeDebugMessenger");

		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;

		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		VkResult result = VK_RESULT_MAX_ENUM;
		if (func != nullptr) {
			result = func(instance, &createInfo, nullptr, debugMessenger);
		}
		FE_LOG_ERROR(result != VK_SUCCESS, "Failed to set up debug messenger!");
	}

	void terminateDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
	{
		FE_SCOPE_TRACE("Startup", "FE::terminateDebugMessenger");
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

}