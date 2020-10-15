#pragma once

#include <exception>
#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/IRenderSystem.h"
#include "graphics/OpenGL/GLWindow.h"

namespace GE
{

	template <typename U>
	using uPtr = std::unique_ptr<U>;

	class GLRenderSystem final : public IRenderSystem
	{
		public:
			GLRenderSystem(const std::string & windowTitle,
			               const uint windowWidth,
			               const uint windowHeight);
			~GLRenderSystem();

			// Actions
			void clear()             const override;
			void render()            const override;
			void pollEvents()        const override;
			void swapBuffers()       const override;
			int  windowShouldClose() const override;

		private:
			void initGLFW() const;
			void initGLEW() const;

		private:
			uPtr<GLWindow> m_window   = nullptr;
			GLFWwindow * m_GLFWwindow = nullptr;
	};

} // GE
