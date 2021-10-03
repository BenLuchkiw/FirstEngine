#pragma once

#include "FirstEngineInclude.hpp"

#include "FirstEngine.hpp"

int main()
{
	FE_BEGIN_TRACING("C:/Programming/FirstEngine/libs/minitrace/trace.json") // TODO make this a relative path using cmake
	FE_THREAD_NAME("Main Thread")
	{
		FE_LOG_WARNING(false, "ahhhhh!");

		FE_SCOPE_TRACE("Program", "Main")
		FE::FirstEngine app;
		app.run();
	}
	
	FE_END_TRACING
	return 0;
}
