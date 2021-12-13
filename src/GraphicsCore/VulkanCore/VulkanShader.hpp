#pragma once

#include "Core/FirstEngineInclude.hpp"

#include "VulkanRenderer.hpp"

namespace FE
{
	// Forward declarations
	class Renderer;

	enum ShaderType
	{
		FE_SHADER_TYPE_VERTEX = 0,
		//FE_SHADER_TYPE_TESSELLATION = 1,
		//FE_SHADER_TYPE_GEOMETRY = 2,
		FE_SHADER_TYPE_FRAGMENT = 3
	};

	class Shader
	{
	public:
		Shader(Renderer* renderer, const std::string& filename, ShaderType shaderType)
			: m_renderer(renderer)
		{
			FE_SCOPE_TRACE("Startup", "FE::Shader::Shader");

			std::string fileLocation = std::string(ROOT_DIR + std::string("/src/GraphicsCore/Resources/Shaders/") + filename);
			std::ifstream file(fileLocation, std::ios::ate | std::ios::binary);
			
			FE_LOG_ERROR(!file.is_open(), "Vulkan failed to open the shader file called: " + filename);

			size_t size = 0;
			size = (size_t)file.tellg();
			std::vector<char> shader(size);
			file.seekg(0);
			file.read(shader.data(), size);
			file.close();

			VkShaderModuleCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.pNext;
			createInfo.flags;
			createInfo.codeSize = shader.size();
			createInfo.pCode = reinterpret_cast<const uint32_t*>(shader.data());

			FE_LOG_ERROR(vkCreateShaderModule(m_renderer->getDevice(), &createInfo, NULL, &m_shaderModule) != VK_SUCCESS, "Vulkan failed to create shader module");
		}

		~Shader()
		{
			vkDestroyShaderModule(m_renderer->getDevice(), m_shaderModule, NULL);
		}

		VkShaderModule& getShaderModule() { return m_shaderModule; }
	private: // Methods
		
	private: // Members
		VkShaderModule m_shaderModule;

		Renderer* m_renderer;
	};
}