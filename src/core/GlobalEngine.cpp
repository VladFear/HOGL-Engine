#include <iostream>

#include "core/GlobalEngine.h"
#include "core/EngineArgs.h"

#include "graphics/GameScene.h"
#include "graphics/Camera.h"
#include "graphics/OpenGL/GLRenderSystem.h"
#include "graphics/OpenGL/GLWindow.h"

namespace GE
{

	// GlobalEngine class

	GlobalEngine::GlobalEngine(const EngineArgs & engineArgs) :
		m_impl { std::make_unique<GlobalEngineImpl>(engineArgs) }
	{ }

	void GlobalEngine::startGameLoop() const
	{
		m_impl->startGameLoop();
	}

	void GlobalEngine::setGameScene(std::shared_ptr<GameScene> gameScene)
	{
		m_impl->setGameScene(gameScene);
	}

	void GlobalEngine::setCamera(std::shared_ptr<Camera> camera)
	{
		m_impl->setCamera(camera);
	}

	// GlobalEngineImpl class

	GlobalEngine::GlobalEngineImpl::GlobalEngineImpl(const EngineArgs & engineArgs) :
		m_engineArgs { engineArgs }
	{
		switch (engineArgs.engineAPI)
		{
			case GE::EngineAPI::OpenGL:
				initGLFW();
				createGLFWwindow(engineArgs.windowTitle,
				                 engineArgs.windowWidth,
				                 engineArgs.windowHeight);
				initGLEW();
				initGLRenderSystem();
				break;
			default:
				std::cerr << "Unsupported Engine API!\n";
				std::terminate();
		}
	}

	void GlobalEngine::GlobalEngineImpl::startGameLoop() const
	{
		while (!m_window->windowShouldClose())
		{
			/* Poll for and process events */
			m_window->pollEvents();

			m_window->clear();

			/* Render here */
			m_renderSystem->render(m_gameScene, m_camera);

			/* Swap front and back buffers */
			m_window->swapBuffers();
		}
	}

	void GlobalEngine::GlobalEngineImpl::setGameScene(std::shared_ptr<GameScene> gameScene)
	{
		m_gameScene = gameScene;

		m_renderSystem->prepareGameScene(m_gameScene);
	}

	void GlobalEngine::GlobalEngineImpl::setCamera(std::shared_ptr<Camera> camera)
	{
		m_camera = camera;
	}

	void GlobalEngine::GlobalEngineImpl::initGLFW()
	{
		if (!glfwInit())
			throw std::runtime_error(std::string("Failed to initialize GLFW library.\n"));

		// Enable MSAA
		glfwWindowHint(GLFW_SAMPLES, 4);
	}

	void GlobalEngine::GlobalEngineImpl::initGLEW()
	{
		if (glewInit() != GLEW_OK)
			throw std::runtime_error(std::string("Failed to initialize GLEW library. glewInit() != GLEW_OK.\n"));
	}

	void GlobalEngine::GlobalEngineImpl::createGLFWwindow(const std::string & windowTitle,
	                                                      const uint windowWidth,
	                                                      const uint windowHeight)
	{
		m_window = std::make_unique<GLWindow>(windowTitle,
		                                      windowWidth,
		                                      windowHeight);
	}

	void GlobalEngine::GlobalEngineImpl::initGLRenderSystem()
	{
		m_renderSystem = std::make_unique<GLRenderSystem>();
	}

} // GE
