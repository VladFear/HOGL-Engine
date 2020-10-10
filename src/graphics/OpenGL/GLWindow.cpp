#include <graphics/OpenGL/GLWindow.h>

namespace GE
{

	GLWindow::GLWindow() : Window()
	{
		createWindow();
	}

	GLWindow::GLWindow(const std::string & title,
	                   const uint width,
	                   const uint height) :
		Window(title, width, height)
	{
		createWindow();
	}

	void GLWindow::createWindow()
	{
		m_window.reset(
			glfwCreateWindow(Window::m_dimensions.width,
			                 Window::m_dimensions.height,
			                 Window::m_title.c_str(),
			                 nullptr,
			                 nullptr));

		if (!m_window)
			throw std::runtime_error(std::string("Failed to create OpenGL window context.\n"));

		/* Make the window's context current */
		glfwMakeContextCurrent(m_window.get());
	}

	void GLWindow::swapBuffers() const
	{
		glfwSwapBuffers(m_window.get());
	}

	GLint GLWindow::windowShouldClose() const
	{
		return glfwWindowShouldClose(m_window.get());
	}

	GLFWwindow * GLWindow::getGLFWwindow() const
	{
		return m_window.get();
	}

} // GE
