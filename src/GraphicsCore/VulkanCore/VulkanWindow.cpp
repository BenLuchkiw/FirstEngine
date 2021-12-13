#include "VulkanWindow.hpp"

#include "VulkanRenderer.hpp"

namespace FE
{
	Window::Window(Renderer* renderer, VkExtent2D screenDimensions, const std::string& windowName)
		: m_renderer(renderer), m_screenExtent(screenDimensions), m_windowName(windowName)
	{
		FE_SCOPE_TRACE("Startup", "FE::Window::Window");

		createWindow();
		createSwapchain();
		createImageViews();
		createPipelines();
	}

	Window::~Window()
	{
		FE_SCOPE_TRACE("Cleanup", "FE::Window::~Window");

		for (const auto& imageView : m_imageViews)
		{
			vkDestroyImageView(m_renderer->getDevice(), imageView, NULL);
		}
		
		vkDestroySwapchainKHR(m_renderer->getDevice(), m_swapchain, NULL);
		vkDestroySurfaceKHR(m_renderer->getInstance(), m_surface, NULL);
		glfwDestroyWindow(m_window);
	}

	void Window::createWindow()
	{
		FE_SCOPE_TRACE("Startup", "FE::Window::createWindow");
		
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tells opengl not to create opengl context
		m_window = glfwCreateWindow(m_screenExtent.width, m_screenExtent.height, m_windowName.c_str(), NULL, NULL);
		FE_LOG_ERROR(m_window == NULL, "GLFW failed to create a window");


		FE_LOG_ERROR(glfwCreateWindowSurface(m_renderer->getInstance(), m_window, NULL, &m_surface) != VK_SUCCESS, "GLFW Failed to create window surface");
	}

	void Window::createSwapchain()
	{
		FE_SCOPE_TRACE("Running", "FE::VulkanSwapchain::initSwapchain");

		VkBool32 supported;
		vkGetPhysicalDeviceSurfaceSupportKHR(m_renderer->getRenderingDevice(), 0, m_surface, &supported);
		FE_LOG_ERROR(supported != VK_TRUE, "The selected graphics device does not have surface support");

		// Selecting surface cababilities
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_renderer->getRenderingDevice(), m_surface, &m_capabilities);
		uint32_t m_imageCount;
		if (m_capabilities.maxImageCount > 0 && ((m_capabilities.minImageCount + 1) <= m_capabilities.maxImageCount))
		{
			m_imageCount = m_capabilities.minImageCount + 1;
		}
		else
		{
			m_imageCount = m_capabilities.maxImageCount;
			FE_LOG_WARNING(1, "GPU may not be adequate"); // #TODO verify concern and fix this warning
		}

		// Selecting format
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_renderer->getRenderingDevice(), m_surface, &formatCount, NULL);
		FE_LOG_WARNING(formatCount == 0, "Vulkan could not find any surface formats, could be bad, not sure"); // #TODO verify and update this warning
		std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_renderer->getRenderingDevice(), m_surface, &formatCount, surfaceFormats.data());

		m_surfaceFormat = surfaceFormats[0];
		for (const auto& format : surfaceFormats)
		{
			if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				m_surfaceFormat = format;
			}
		}

		// Getting extent
		if (m_capabilities.currentExtent.height != UINT32_MAX)
		{
			m_pixelExtent = m_capabilities.currentExtent;
		}
		else
		{
			int height;
			int width;
			glfwGetFramebufferSize(m_window, &width, &height);
			m_screenExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

			// #TODO verify and edit these appropriately
			FE_LOG_ERROR((m_screenExtent.width < m_capabilities.minImageExtent.width) || (m_screenExtent.width > m_capabilities.maxImageExtent.width), "Vulkan screen extent was not within bounds");
			FE_LOG_ERROR((m_screenExtent.height < m_capabilities.minImageExtent.height) || (m_screenExtent.height > m_capabilities.maxImageExtent.height), "Vulkan screen extent was not within bounds");
		}

		// Selecting present mode
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_renderer->getRenderingDevice(), m_surface, &presentModeCount, NULL);
		std::vector<VkPresentModeKHR> presentModes(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_renderer->getRenderingDevice(), m_surface, &presentModeCount, presentModes.data());
		m_presentMode = VK_PRESENT_MODE_FIFO_KHR;
		for (const auto& presentMode : presentModes)
		{
			if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				m_presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
			}
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.pNext;
		createInfo.flags;
		createInfo.surface = m_surface;
		createInfo.minImageCount = m_imageCount;
		createInfo.imageFormat = m_surfaceFormat.format;
		createInfo.imageColorSpace = m_surfaceFormat.colorSpace;
		createInfo.imageExtent = m_screenExtent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = NULL;
		createInfo.preTransform = m_capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = m_presentMode;
		createInfo.clipped = VK_TRUE; // #TODO this needs more research, and may end up needing to be changed for simulations
		createInfo.oldSwapchain; // #Resizing will need this

		vkCreateSwapchainKHR(m_renderer->getDevice(), &createInfo, NULL, &m_swapchain);
	}

	void Window::recreateSwapchain()
	{
		FE_SCOPE_TRACE("Running", "FE::Window::recreateSwapchain");
	}

	void Window::createImageViews()
	{
		FE_SCOPE_TRACE("Running", "FE::Window::createImageViews");

		vkGetSwapchainImagesKHR(m_renderer->getDevice(), m_swapchain, &m_imageCount, NULL);
		m_images.resize(m_imageCount);
		vkGetSwapchainImagesKHR(m_renderer->getDevice(), m_swapchain, &m_imageCount, m_images.data());

		m_imageViews.resize(m_imageCount);
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.pNext;
		createInfo.flags;
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = m_surfaceFormat.format;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.layerCount = 1;
		createInfo.subresourceRange.levelCount = 1;

		for (int i = 0; i < m_imageCount; i++)
		{
			createInfo.image = m_images[i];
			FE_LOG_ERROR(vkCreateImageView(m_renderer->getDevice(), &createInfo, NULL, &m_imageViews[i]) != VK_SUCCESS, "Vulkan failed to create image view");
		}
	}

	void Window::createPipelines()
	{
		m_pipeline.emplace_back(std::make_unique<Pipeline>(m_renderer, this, "SimpleVertex.spv", "SimpleFragment.spv"));
	}
}