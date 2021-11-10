#pragma once

#include "FirstEngineInclude.hpp"

#include "FirstEngine.hpp"

int main()
{
	try
	{
		std::string dir = ROOT_DIR;
		dir += "/libs/minitrace/trace.json";
		
		FE_BEGIN_TRACING(dir.c_str()); // #TODO make this a relative path using cmake
		__FILE__;
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
