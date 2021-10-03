#pragma once

#include "Core/FirstEngineInclude.hpp"

#include "GraphicsCore/Renderer.hpp"
#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

#include "GraphicsCore/Renderer.hpp"

namespace FE
{
	class VulkanRenderer : public Renderer
	{
	public:// Public Methods
		VulkanRenderer();
		~VulkanRenderer();

	private:// Private Methods
		void createInstance();
		void pickPhysicalDevice(); // currently selects the first available device
		void setupLogicalDevice();

	private:// Member data
		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_debugMessenger;

		std::vector<VkPhysicalDevice> m_physicalDevices;
		VkPhysicalDevice m_renderingDevice; // TODO if compute gets used add an optional compute device that may be identical to this one
		std::vector<VkPhysicalDeviceProperties> m_physicalDeviceProperties;

		VkDevice m_device;
	};
}