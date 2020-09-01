#include <graphics/openglwindow.h>

OpenGLWindow::OpenGLWindow(std::string title,
                           unsigned int width,
                           unsigned int height) :
	Window(title, width, height)
{
	createWindow();
}

void OpenGLWindow::createWindow()
{
	m_window.reset(glfwCreateWindow(Window::m_windimens.width,
	                                Window::m_windimens.height,
	                                Window::m_title.c_str(),
	                                nullptr,
	                                nullptr));

	if (!m_window)
	{
		glfwTerminate();
		throw std::runtime_error(std::string("Failed to create window context.\n"));
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window.get());
}

void OpenGLWindow::clear() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::swapBuffers() const
{
	glfwSwapBuffers(m_window.get());
}

int OpenGLWindow::windowShouldClose() const
{
	return glfwWindowShouldClose(m_window.get());
}
