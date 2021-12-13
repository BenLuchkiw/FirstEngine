#include "FirstEngineInclude.hpp"


#include "FirstEngine.hpp"

#include "GraphicsCore/VulkanCore/VulkanShader.hpp"

namespace FE
{
	FirstEngine::FirstEngine()
	{
		FE_SCOPE_TRACE("Startup", "FirstEngine::FirstEngine");
		FE_LOG_INFO(1, "Starting");
		
		FE_TRACING_FLUSH;
	}

	FirstEngine::~FirstEngine()
	{
		FE_SCOPE_TRACE("Cleanup", "FirstEngine::~FirstEngine()");
		FE_LOG_INFO(1, "Ending");

		FE_TRACING_FLUSH;
	}

	void FirstEngine::run()
	{
		FE_SCOPE_TRACE("Running", "FirstEngine::run()");
		FE_LOG_INFO(1, "Running");

		renderer.createWindow(800, 600, "First Window");
		renderer.createWindow(200, 200, "Second Window");
		while (!renderer.shouldExit())
		{
			renderer.draw();
		}
		FE_TRACING_FLUSH;
	}
}

//        /* Loop until the user closes the window */
//while (!glfwWindowShouldClose(m_window.get()))
//{
//    /* Render here */
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    /* Swap front and back buffers */
//    glfwSwapBuffers(m_window.get());
//
//    /* Poll for and process events */
//    glfwPollEvents();
//}
