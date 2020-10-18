#include "graphics/OpenGL/GLWindow.h"

namespace GE
{

	GLWindow::GLWindow(const std::string & title,
	                   const uint width,
	                   const uint height) :
		IWindow { title, width, height }
	{
		m_window.reset(
			glfwCreateWindow(IWindow::m_width,
			                 IWindow::m_height,
			                 IWindow::m_title.c_str(),
			                 nullptr,
			                 nullptr));

		if (!m_window)
			throw std::runtime_error(std::string("Failed to create OpenGL window context.\n"));

		/* Make the window's context current */
		glfwMakeContextCurrent(getGLFWwindow());

		initGLFWCallbacks();
	}

	GLFWwindow * GLWindow::getGLFWwindow() const
	{
		return m_window.get();
	}

	void GLWindow::initGLFWCallbacks()
	{
		glfwSetKeyCallback(getGLFWwindow(), keyCallback);
	}

	void GLWindow::pollEvents() const
	{
		glfwPollEvents();
	}

	void GLWindow::swapBuffers() const
	{
		glfwSwapBuffers(getGLFWwindow());
	}

	void GLWindow::clear() const
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	int GLWindow::windowShouldClose() const
	{
		return glfwWindowShouldClose(getGLFWwindow());
	}

	void GLWindow::keyCallback(GLFWwindow * window,
	                           int key,
	                           int scancode,
	                           int action,
	                           int mods)
	{
		(void)window;
		(void)scancode;
		(void)mods;
		(void)key;
		(void)action;
	}

} // GE
