#pragma once

#include "Core/FirstEngineInclude.hpp"

#include "vulkan/vulkan.h"

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "VulkanPipeline.hpp"

namespace FE
{
	// Forward declaration
	class Renderer;

	class Window
	{
	public:
		Window(Renderer* renderer, VkExtent2D screenDimensions, const std::string& windowName);
		Window() = delete;
		~Window();

		std::string& getWindowName() { return m_windowName; }
		bool shouldWindowClose() { return glfwWindowShouldClose(m_window); }
		GLFWwindow* getWindow() { return m_window; }

		// For vulkan internal use only
		VkExtent2D getScreenExtent() { return m_screenExtent; }
		VkExtent2D getPixelExtent() { return m_pixelExtent; }
		VkSurfaceFormatKHR getSurfaceFormat() { return m_surfaceFormat; }

	private: // Methods
		void createWindow();
		void createSwapchain();
		void recreateSwapchain(); // Requires a currently valid swapchain
		void createImageViews();
		void createPipelines();

	private: // Members
		// Owned
		VkSwapchainKHR m_swapchain;
		VkSurfaceKHR m_surface;
		std::vector<VkImage> m_images;
		std::vector<VkImageView> m_imageViews;
		uint32_t m_imageCount;

		GLFWwindow* m_window;

		std::string m_windowName;

		// Details about current swapchain
		VkSurfaceCapabilitiesKHR m_capabilities;
		VkSurfaceFormatKHR m_surfaceFormat;
		VkPresentModeKHR m_presentMode;

		VkExtent2D m_pixelExtent;
		VkExtent2D m_screenExtent;

		std::vector<std::unique_ptr<Pipeline>> m_pipeline;

		// Not owned
		Renderer* m_renderer;
	};
}