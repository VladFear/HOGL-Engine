#pragma once

#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/IWindow.h"

namespace GE
{

	struct GLFWwindowDeleter
	{
		void operator()(GLFWwindow * window)
		{
			glfwDestroyWindow(window);
		}
	};

	class GLWindow final : public IWindow
	{
		public:
			GLWindow(const std::string & title,
			         const uint width,
			         const uint height);
			~GLWindow() = default;

			GLWindow() = delete;
			GLWindow(const GLWindow &) = delete;
			GLWindow & operator=(const GLWindow &) = delete;

			// Getters
			GLFWwindow * getGLFWwindow() const;

		protected:
			void createWindow() override;

		private:
			std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_window;
	};

} // GE
