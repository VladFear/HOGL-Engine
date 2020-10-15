#include "GlobalEngine.h"

namespace GE
{

	GlobalEngine::GlobalEngine(EngineAPI api)
	{
		switch (api)
		{
			case EngineAPI::OpenGL:
				m_renderSystem = std::make_unique<GLRenderSystem>();
				break;
			default:
				std::cerr << "Unsupported Engine API!\n";
				std::terminate();
		}

		m_api = api;
		m_gameScene = std::make_unique<GameScene>();
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

	void GlobalEngine::render() const
	{
		m_gameScene->renderScene();
	}

	void GlobalEngine::addGameObject(uPtr<GameObject> gameObject)
	{
		m_gameScene->addGameObject(std::move(gameObject));
	}

} // GE
