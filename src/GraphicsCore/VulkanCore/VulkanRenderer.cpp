#include "VulkanRenderer.hpp"

#include "VulkanValidationLayers.hpp"
namespace FE
{
	//Public methods

	VulkanRenderer::VulkanRenderer()
	{
		glfwInit();
		FE_LOG_ERROR(!glfwVulkanSupported(), "glfw does not support Vulkan!");

		createInstance();
		initializeDebugMessenger(m_instance, &m_debugMessenger);

		pickPhysicalDevice();
	}

	VulkanRenderer::~VulkanRenderer()
	{
		terminateDebugMessenger(m_instance, m_debugMessenger, nullptr);

		vkDestroyInstance(m_instance, nullptr);
	}

	// Private methods

	void VulkanRenderer::createInstance()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "First Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Query GLFW for extensions and extension count
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pNext = NULL;
		createInfo.flags = 0;
		createInfo.pApplicationInfo = &appInfo;
		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		
		if (initValidationLayers())
		{
			createInfo.enabledLayerCount = 1;
			// A hack to get validation layers working, feel free to fix
			const char* layerNames = "VK_LAYER_KHRONOS_validation";
			createInfo.ppEnabledLayerNames = &layerNames;

		}// else layer count and layer names are already set to null

		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
		{
			FE_LOG_ERROR(true, "Failed to create Vulkan instance");
		}
	}
	void VulkanRenderer::pickPhysicalDevice()
	{
		uint32_t deviceCount;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, NULL);
		FE_LOG_ERROR(deviceCount == 0, "Vulkan Failed to find a suitable device");
		m_physicalDevices.resize(deviceCount);

		vkEnumeratePhysicalDevices(m_instance, &deviceCount, m_physicalDevices.data());
		m_renderingDevice = m_physicalDevices[0];

		for (int i = 0; i < m_physicalDevices.size(); i++)
		{
			VkPhysicalDeviceProperties data;
			vkGetPhysicalDeviceProperties(m_physicalDevices.at(i), &data);
			m_physicalDeviceProperties.push_back(data);
		}
	}

	void VulkanRenderer::setupLogicalDevice()
	{

		// queue creation
		VkDeviceQueueCreateInfo queueCreateInfo;
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.pNext = NULL;
		queueCreateInfo.flags;
		queueCreateInfo.queue


		// device creation
		VkDeviceCreateInfo createInfo;

		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pNext = NULL;
		//createInfo.flags     //reserved for future use
		createInfo.queueCreateInfoCount
	}


}