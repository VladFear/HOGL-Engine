#include <iostream>

#include "core/GlobalEngine.h"
#include "core/EngineArgs.h"

#include "TestApplication.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
	try
	{
		EngineArgs engineArgs =
			EngineArgsBuilder()
			.setEngineAPI(EngineAPI::OpenGL)
			.setWindowTitle("TestApplication")
			.build();

		auto engine  = createUnique<GlobalEngine>(engineArgs);
		auto gameApp = createUnique<TestApplication>(std::move(engine));

		gameApp->startGameLoop();
	}
	catch (const std::exception & ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
