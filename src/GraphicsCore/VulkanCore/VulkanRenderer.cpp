
#include "VulkanRenderer.hpp"

#include "VulkanValidationLayers.hpp"
#include "VulkanRenderer.hpp"

namespace FE
{
	//Public methods

	Renderer::Renderer()
	{
		FE_SCOPE_TRACE("Startup", "FE::Renderer::Renderer");

		// Initializing vars
		m_requiredDeviceExtensions.push_back("VK_KHR_swapchain");

		glfwInit();
		FE_LOG_ERROR(!glfwVulkanSupported(), "glfw does not support Vulkan!");

		createInstance();
		initializeDebugMessenger(m_instance, &m_debugMessenger);

		pickPhysicalDevice();
		setupLogicalDevice();
	}

	Renderer::~Renderer()
	{
		FE_SCOPE_TRACE("Cleanup", "FE::Renderer::~Renderer");

		m_windows.clear();
		//m_compute.clear(); #Compute

		vkDestroyDevice(m_device, NULL);

		if (VULKAN_VALIDATION_LAYERS)
		{
			terminateDebugMessenger(m_instance, m_debugMessenger, NULL);
		}
		vkDestroyInstance(m_instance, NULL);

		glfwTerminate();
	}

	void Renderer::draw()
	{
		FE_SCOPE_TRACE("Running", "FE::Renderer::draw");
		for (int i = 0; i < m_windows.size(); i++)
		{
			if (m_windows[i].get()->shouldWindowClose())
			{
				m_windows.erase(m_windows.begin() + i);
				break;
			}
			
			/* Poll for and process events */
			glfwPollEvents();
		}

		if (m_windows.size() == 0)
		{
			running = false;
		}
	}

	void Renderer::createWindow(uint32_t width, uint32_t height, const std::string& windowName)
	{
		FE_SCOPE_TRACE("Running", "FE::Renderer::createWindow");
		m_windows.emplace_back(std::make_unique<Window>(m_instance, m_renderingDevice, m_device, VkExtent2D(width, height), windowName));
	}

	// Private methods

	void Renderer::createInstance()
	{
		FE_SCOPE_TRACE("Startup", "FE::Renderer::createInstance");

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "First Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pNext = NULL;
		createInfo.flags = 0;
		createInfo.pApplicationInfo = &appInfo;
		auto extensions = getRequiredExtensions(); // gets all glfw extensions
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();


		if (initValidationLayers())
		{
			createInfo.enabledLayerCount = 1;
			// A hack to get validation layers working, feel free to fix
			const char* layerNames = "VK_LAYER_KHRONOS_validation";
			createInfo.ppEnabledLayerNames = &layerNames;

		}// else layer count and layer names are already set to null

		VkInstance tempInstance;
		FE_LOG_ERROR(vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS, "Failed to create Vulkan instance");
	}

	void Renderer::pickPhysicalDevice() // #TODO make this function pick the best device not the first capable
	{
		FE_SCOPE_TRACE("Startup", "FE::Renderer::pickPhysicalDevice");

		uint32_t deviceCount;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, NULL);
		FE_LOG_ERROR(deviceCount == 0, "Vulkan Failed to find a suitable device");
		m_physicalDevices.resize(deviceCount);

		vkEnumeratePhysicalDevices(m_instance, &deviceCount, m_physicalDevices.data());

		bool found = false;
		for (int i = 0; i < m_physicalDevices.size(); i++)
		{
			if (glfwGetPhysicalDevicePresentationSupport(m_instance, m_physicalDevices[i], m_graphicsQueueIndex))
			{
				m_renderingDevice = m_physicalDevices[i];
				found = true;
			}
		}
		FE_LOG_ERROR(!found, "Vulkan Failed to find a suitable device");

		for (int i = 0; i < m_physicalDevices.size(); i++)
		{
			VkPhysicalDeviceProperties data;
			vkGetPhysicalDeviceProperties(m_physicalDevices.at(i), &data);
			m_physicalDeviceProperties.push_back(data);
		}
	}

	void Renderer::setupLogicalDevice()
	{
		FE_SCOPE_TRACE("Startup", "FE::Renderer::setupLogicalDevice");

		uint32_t queueCount;

		vkGetPhysicalDeviceQueueFamilyProperties(m_renderingDevice, &queueCount, NULL);
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueCount);
		FE_LOG_ERROR(queueCount == 0, "Vulkan rendering device has no available queues");
		vkGetPhysicalDeviceQueueFamilyProperties(m_renderingDevice, &queueCount, queueFamilyProperties.data());

		for (int i = 0; i < queueCount; i++)
		{
			m_queueFamilies.push_back({ queueFamilyProperties[i] });
		}

		// queue creation
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.pNext = NULL;
		queueCreateInfo.flags; // not currently required
		queueCreateInfo.queueFamilyIndex = m_graphicsQueueIndex;
		queueCreateInfo.queueCount = 1.0f; // #Compute will require this to be an array, and next line to differ
		const float priority = 1.0f;
		queueCreateInfo.pQueuePriorities = &priority;


		VkPhysicalDeviceFeatures features = {}; // #Features

		// device creation
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pNext = NULL;
		deviceCreateInfo.flags; // reserved for future use
		deviceCreateInfo.queueCreateInfoCount = 1; // #Compute may need this to change as well as next line
		deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
		deviceCreateInfo.enabledLayerCount; // deprecated and ignored
		deviceCreateInfo.ppEnabledLayerNames; // deprecated and ignored
		deviceCreateInfo.pEnabledFeatures = &features;

		// #TODO verify extensions
		deviceCreateInfo.enabledExtensionCount = m_requiredDeviceExtensions.size();
		deviceCreateInfo.ppEnabledExtensionNames = m_requiredDeviceExtensions.data();

		FE_LOG_ERROR(vkCreateDevice(m_renderingDevice, &deviceCreateInfo, NULL, &m_device) != VK_SUCCESS, "Vulkan failed to create logical device");
	}
}