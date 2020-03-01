#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <graphics/iwindow.h>
#include <memory>

struct DestroyGLFWwindow
{
	void operator()(GLFWwindow * window)
	{
		glfwDestroyWindow(window);
	}
};

class OpenGLWindow final : public IWindow
{
	private:
		std::unique_ptr<GLFWwindow, DestroyGLFWwindow> m_window;

	public:
		explicit OpenGLWindow(std::string title,
		                      unsigned int width,
		                      unsigned int height);

		OpenGLWindow(const OpenGLWindow &) = delete;
		GLFWwindow * getGLFWwindow() const { return m_window.get(); }
		void swapBuffers() const;
		void clear() const;

	protected:
		void createWindow() override;
};
