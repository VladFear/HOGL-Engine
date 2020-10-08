#include <graphics/RenderEngine.h>

RenderEngine::RenderEngine(EngineAPI api)
{
	switch (api)
	{
		case EngineAPI::OpenGL:
			initOpenGL();
			break;
		case EngineAPI::Vulkan:
			std::cerr << "Vulkan API currently is not supported\n";
			std::terminate();
			break;
		default:
			std::cerr << "Unsupported API\n";
			std::terminate();
	}

	m_current_api = api;
}

RenderEngine::~RenderEngine()
{
	if (m_current_api == EngineAPI::OpenGL)
		glfwTerminate();
}

void RenderEngine::render() const
{

}

void RenderEngine::pollEvents() const
{
	glfwPollEvents();
}

void RenderEngine::swapBuffers() const
{
	m_window->swapBuffers();
}

void RenderEngine::clear() const
{
	m_window->clear();
}

int RenderEngine::windowShouldClose() const
{
	return m_window->windowShouldClose();
}

void RenderEngine::initOpenGL()
{
	initGLFW();

	glfwWindowHint(GLFW_SAMPLES, 4);

	m_window = std::make_unique<OpenGLWindow>();
	initGLEW();
}

void RenderEngine::initGLFW() const
{
	if (!glfwInit())
		throw std::runtime_error(std::string("Failed to initialize GLFW library.\n"));
}

void RenderEngine::initGLEW() const
{
	if (glewInit() != GLEW_OK)
		throw std::runtime_error(std::string("Failed to initialize GLEW library. glewInit() != GLEW_OK\n"));
}
