#pragma once

#include "FirstEngineInclude.hpp"

#include "FirstEngine.hpp"

int main()
{
	try
	{		
		FE_BEGIN_TRACING(std::string(ROOT_DIR + "/libs/minitrace/trace.json").c_str());

		FE_THREAD_NAME("Main Thread");
		{
			FE_SCOPE_TRACE("Program", "Main");
			FE::FirstEngine app;
			app.run();
		}

		FE_END_TRACING;
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();

		FE_END_TRACING;

		return -1;
	}
	return 0;
}
