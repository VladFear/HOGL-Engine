#include <graphics/OpenGL/GLRenderSystem.h>

namespace GE
{

	GLRenderSystem::GLRenderSystem()
	{
		initOpenGL();
	}

	GLRenderSystem::~GLRenderSystem()
	{
		glfwTerminate();
	}

	void GLRenderSystem::render() const
	{
		// TODO:
	}

	void GLRenderSystem::pollEvents() const
	{
		glfwPollEvents();
	}

	void GLRenderSystem::swapBuffers() const
	{
		m_window->swapBuffers();
	}

	void GLRenderSystem::clear() const
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	int GLRenderSystem::windowShouldClose() const
	{
		return m_window->windowShouldClose();
	}

	void GLRenderSystem::initOpenGL()
	{
		initGLFW();

		glfwWindowHint(GLFW_SAMPLES, 4);

		m_window = std::make_unique<GLWindow>();
		initGLEW();
	}

	void GLRenderSystem::initGLFW() const
	{
		if (!glfwInit())
			throw std::runtime_error(std::string("Failed to initialize GLFW library.\n"));
	}

	void GLRenderSystem::initGLEW() const
	{
		if (glewInit() != GLEW_OK)
			throw std::runtime_error(std::string("Failed to initialize GLEW library. glewInit() != GLEW_OK\n"));
	}

} // GE
