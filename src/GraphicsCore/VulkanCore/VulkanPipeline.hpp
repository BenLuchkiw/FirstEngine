#pragma once

#include "vulkan/vulkan.h"

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "Core/FirstEngineInclude.hpp"
#include "VulkanShader.hpp"

namespace FE
{
	// Forward declarations
	class Renderer;
	class Window;

	class Pipeline
	{
	public:
		Pipeline(Renderer* renderer, Window* window, const std::string& vertexFilename, const std::string& fragmentFilename);
		~Pipeline();

	private: // Methods
		void createPipeline();
	private: // Members
		VkPipeline m_pipeline;
		VkRenderPass m_renderPass;
		VkPipelineLayout m_pipelineLayout;


		Shader m_fragmentShader;
		//Shader tessellationShader;
		//Shader geometryShader;
		Shader m_vertexShader;

		// Pointers to parents
		Renderer* m_renderer;
		Window* m_window;
	};
}