#include "FirstEngineInclude.hpp"


#include "FirstEngine.hpp"

namespace FE
{
	FirstEngine::FirstEngine()
	{
		FE_SCOPE_TRACE("Startup", "FirstEngine::FirstEngine");
		FE_LOG_VERBOSE("Starting")
		
		FE_TRACING_FLUSH
	}

	FirstEngine::~FirstEngine()
	{
		FE_SCOPE_TRACE("Cleanup", "FirstEngine::~FirstEngine()");
		FE_LOG_VERBOSE("Ending")

		FE_TRACING_FLUSH
	}

	void FirstEngine::run()
	{
		FE_SCOPE_TRACE("Run", "FirstEngine::run()");
		FE_LOG_VERBOSE("Running")

		FE_TRACING_FLUSH
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
