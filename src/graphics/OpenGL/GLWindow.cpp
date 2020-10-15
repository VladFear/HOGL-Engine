#include "graphics/OpenGL/GLWindow.h"

namespace GE
{

	GLWindow::GLWindow(const std::string & title,
	                   const uint width,
	                   const uint height) :
		IWindow(title, width, height)
	{
		createWindow();
	}

	void GLWindow::createWindow()
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
		glfwMakeContextCurrent(m_window.get());
	}

	GLFWwindow * GLWindow::getGLFWwindow() const
	{
		return m_window.get();
	}

} // GE
