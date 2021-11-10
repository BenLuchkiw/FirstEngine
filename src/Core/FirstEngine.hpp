#pragma once

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

#include "GraphicsCore/VulkanCore/VulkanRenderer.hpp"

namespace FE
{
	class FirstEngine
	{
	public:
		FirstEngine();
		~FirstEngine();

		void run();
	private:
		Renderer renderer;
	};
}
