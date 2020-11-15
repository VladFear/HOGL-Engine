#pragma once

#include <boost/signals2/signal.hpp>

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

	using namespace boost::signals2;
	class Camera;

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
			void closeWindow()       const override;
			int  windowShouldClose() const override;

			void setMoveCameraSignal(Shared<Camera> camera) override;
			void emitMoveCameraSignal(const glm::vec3 & move);

		private:
			void initGLFWCallbacks();
			GLFWwindow * getGLFWwindow() const;

		private:
			std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_window;
			signal<void(GLFWwindow*, int)> closeWindowSignal;
			signal<void(const glm::vec3 &)> moveCameraSignal;
	};

} // GE
