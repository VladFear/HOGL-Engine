#include <graphics/GlobalEngine.h>

GlobalEngine::GlobalEngine(EngineAPI api,
                           std::string title,
                           unsigned int width,
                           unsigned int height)
{
	switch (api)
	{
		case EngineAPI::OpenGL_API:
			initGLFW();
			m_window.reset(new OpenGLWindow(title, width, height));
			initGLEW();
			break;
		case EngineAPI::Vulkan_API:
			break;
		default:
			std::cerr << "Unsupported API\n";
			break;
	}
}

GlobalEngine::~GlobalEngine()
{
	glfwTerminate();
}

void GlobalEngine::initGLFW() const
{
	if (!glfwInit())
		throw std::runtime_error(std::string("Failed to initialize GLFW library.\n"));
}

void GlobalEngine::initGLEW() const
{
	if (glewInit() != GLEW_OK)
		throw std::runtime_error(std::string("Failed to initialize GLEW library. glewInit() != GLEW_OK\n"));
}

void GlobalEngine::pollEvents() const
{
	glfwPollEvents();
}

void GlobalEngine::gameLoop() const
{
	while (!m_window->windowShouldClose())
	{
		/* Poll for and process events */
		pollEvents();
		m_window->clear();

		/* Render here */
		render();
		/* Swap front and back buffers */
		m_window->swapBuffers();
	}
}

void GlobalEngine::render() const
{
	m_game_scene->renderScene();
}

void GlobalEngine::setGameScene(GameScene * gameScene)
{
	m_game_scene.reset(gameScene);
}

void GlobalEngine::addGameObject(Model * gameObject)
{
	m_game_scene->addGameObject(gameObject);
}
