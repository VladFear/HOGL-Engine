#pragma once

#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <graphics/Window.h>

struct DestroyGLFWwindow
{
	void operator()(GLFWwindow * window)
	{
		glfwDestroyWindow(window);
	}
};

class OpenGLWindow final : public Window
{
	public:
		OpenGLWindow(std::string title,
		             unsigned int width,
		             unsigned int height);

		OpenGLWindow(const OpenGLWindow &) = delete;
		GLFWwindow * getGLFWwindow() const { return m_window.get(); }
		void swapBuffers() const override;
		void clear() const override;
		int windowShouldClose() const override;

	protected:
		void createWindow() override;

	private:
		std::unique_ptr<GLFWwindow, DestroyGLFWwindow> m_window;
};
