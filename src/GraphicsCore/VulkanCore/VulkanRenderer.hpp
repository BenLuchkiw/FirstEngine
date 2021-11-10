#pragma once

#include "Core/FirstEngineInclude.hpp"

#include "vulkan/vulkan.h"

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "VulkanWindow.hpp"
#include "VulkanValidationLayers.hpp"

namespace FE
{
	class Renderer
	{
	public:
		bool running = true;

		Renderer();
		~Renderer();

		void draw(); // Cycles through all windows and draws for them
		//void compute(); #Compute
		void createWindow(uint32_t width, uint32_t height, const std::string& windowName);  // Some info as parameters... Not sure yet

	private: // Private methods
		void createInstance();
		void pickPhysicalDevice(); // currently selects the first available device
		void setupLogicalDevice();

	private: // Private members
		std::vector<VkPhysicalDevice> m_physicalDevices;
		std::vector<VkPhysicalDeviceProperties> m_physicalDeviceProperties;
		std::vector<VkQueueFamilyProperties> m_queueFamilies;
		VkPhysicalDevice m_renderingDevice;
		VkDevice m_device;
		VkInstance m_instance;
		
		uint32_t m_graphicsQueueIndex = 0;
		//uint32_t m_currentQueueCount = 1; // #Compute

		// The class will sort these vectors and call to submit to queues
		// These are stored on the heap so that copy construction on vector resize doesn't break things #TODO maybe fix...
		std::vector<std::unique_ptr<Window>> m_windows;
		//std::vector<Compute> m_compute #Compute

		std::vector<const char*> m_requiredDeviceExtensions;
		VkDebugUtilsMessengerEXT m_debugMessenger;
	};
}