#include "core/GlobalEngine.h"

namespace GE
{

	GlobalEngine::GlobalEngine(const EngineArgs & engineArgs) :
		m_engineArgs { engineArgs }
	{
		switch (engineArgs.engineAPI)
		{
			case GE::EngineAPI::OpenGL:
				m_renderSystem =
					std::make_unique<GLRenderSystem>(engineArgs.windowTitle,
					                                 engineArgs.windowWidth,
					                                 engineArgs.windowHeight);
				break;
			default:
				std::cerr << "Unsupported Engine API!\n";
				std::terminate();
		}
	}

	void GlobalEngine::startGameLoop() const
	{
		while (!m_renderSystem->windowShouldClose())
		{
			/* Poll for and process events */
			m_renderSystem->pollEvents();
			m_renderSystem->clear();

			/* Render here */
			m_renderSystem->render();

			// TODO: Remove render func
			render();
			/* Swap front and back buffers */
			m_renderSystem->swapBuffers();
		}
	}

	void GlobalEngine::setGameScene(uPtr<GameScene> gameScene)
	{
		m_gameScene = std::move(gameScene);
	}


	void GlobalEngine::render() const
	{
		m_gameScene->renderScene();
	}

} // GE
