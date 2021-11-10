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
	class Pipeline
	{
	public:
		Pipeline(const std::string& vertexFilename, const std::string& fragmentFilename);
	private: // Methods

	private: // Members
		Shader fragmentShader;
		//Shader tessellationShader;
		//Shader geometryShader;
		Shader vertexShader;
	};
}