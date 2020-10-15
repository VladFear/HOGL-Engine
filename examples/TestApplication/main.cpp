#include <iostream>
#include <memory>

#include "core/GlobalEngine.h"
#include "core/EngineArgs.h"

#include "TestApplication.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
	try
	{
		GE::EngineArgs engineArgs =
			GE::EngineArgsBuilder()
			.setEngineAPI(GE::EngineAPI::OpenGL)
			.setWindowTitle("TestApplication")
			.build();

		auto engine  = std::make_unique<GE::GlobalEngine>(engineArgs);
		auto gameApp = std::make_unique<TestApplication>(std::move(engine));

		gameApp->startGameLoop();
	}
	catch (const std::exception & ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
