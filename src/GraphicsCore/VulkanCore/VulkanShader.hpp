#pragma once

#include "Core/FirstEngineInclude.hpp"

namespace FE
{
	enum class ShaderType
	{
		FE_SHADER_TYPE_VERTEX = 0,
		//FE_SHADER_TYPE_TESSELLATION = 1,
		//FE_SHADER_TYPE_GEOMETRY = 2,
		FE_SHADER_TYPE_FRAGMENT = 3
	};

	class Shader
	{
	public:
		Shader(const std::string& filename, ShaderType shaderType)
		{
			FE_SCOPE_TRACE("Startup", "FE::Shader::Shader");
			std::fstream file(filename, std::ios::ate | std::ios::binary);
			
			FE_LOG_ERROR(!file.is_open(), "Vulkan failed to open the shader file called: " + filename);

			size_t size = (size_t)file.tellg();
			m_shader.reserve(size);
			file.seekg(0);
			file.read(m_shader.data(), size);
			file.close();
		}

		std::vector<char>& getShader() { return m_shader; }
	private: // Methods

	private: // Members
		std::vector<char> m_shader;
	};
}