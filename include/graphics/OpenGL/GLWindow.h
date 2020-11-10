#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/Memory.h"
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

			// Actions
			void clear()             const override;
			void pollEvents()        const override;
			void swapBuffers()       const override;
			int  windowShouldClose() const override;

		private:
			void initGLFWCallbacks();
			GLFWwindow * getGLFWwindow() const;

		private:
			// GLFW Callbacks
			static void keyCallback(GLFWwindow * window,
			                        int key,
			                        int scancode,
			                        int action,
			                        int mods);


		private:
			std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_window;
	};

} // GE
