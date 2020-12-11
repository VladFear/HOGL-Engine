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
		glfwSetWindowUserPointer(getGLFWwindow(), this);
		initGLFWCallbacks();
	}

	GLFWwindow * GLWindow::getGLFWwindow() const
	{
		return m_window.get();
	}

	void GLWindow::initGLFWCallbacks()
	{
		closeWindowSignal.connect(&glfwSetWindowShouldClose);

		auto keyCallback = [](GLFWwindow* glfwWindow,
		                      int key,
		                      int scancode,
		                      int action,
		                      int mods)
		{
			(void)scancode;
			(void)mods;
			auto window = static_cast<GLWindow*>(glfwGetWindowUserPointer(glfwWindow));
			const float value = 0.1f;

			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				window->closeWindow();
			else if (key == GLFW_KEY_W && action == GLFW_PRESS)
				window->emitMoveCameraSignal(glm::vec3(0.0f, 0.0f, -value));
			else if (key == GLFW_KEY_S && action == GLFW_PRESS)
				window->emitMoveCameraSignal(glm::vec3(0.0f, 0.0f, value));
			else if (key == GLFW_KEY_D && action == GLFW_PRESS)
				window->emitMoveCameraSignal(glm::vec3(-value, 0.0f, 0.0f));
			else if (key == GLFW_KEY_A && action == GLFW_PRESS)
				window->emitMoveCameraSignal(glm::vec3(value, 0.0f, 0.0f));
		};

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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int GLWindow::windowShouldClose() const
	{
		return glfwWindowShouldClose(getGLFWwindow());
	}

	void GLWindow::closeWindow() const
	{
		closeWindowSignal(getGLFWwindow(), GL_TRUE);
	}

	void GLWindow::setMoveCameraSignal(Shared<Camera> camera)
	{
		moveCameraSignal.connect(boost::bind(&Camera::move, camera, _1));
	}

	void GLWindow::emitMoveCameraSignal(const glm::vec3 & move)
	{
		moveCameraSignal(move);
	}

} // GE
