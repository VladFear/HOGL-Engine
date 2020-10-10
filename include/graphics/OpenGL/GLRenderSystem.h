#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <string>
#include <memory>

#include <graphics/RenderSystem.h>
#include <graphics/OpenGL/GLWindow.h>

namespace GE
{

	template <typename U>
	using uPtr = std::unique_ptr<U>;

	class GLRenderSystem final : public RenderSystem
	{
		public:
			GLRenderSystem();
			~GLRenderSystem();

			// Actions
			void clear()             const override;
			void render()            const override;
			void pollEvents()        const override;
			void swapBuffers()       const override;
			int windowShouldClose()  const override;

		private:
			void initOpenGL();
			void initGLFW() const;
			void initGLEW() const;
	};

} // GE
