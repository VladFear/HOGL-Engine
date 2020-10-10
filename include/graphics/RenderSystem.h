#pragma once

#include <memory>

#include <graphics/Window.h>

namespace GE
{

	template <typename U>
	using uPtr = std::unique_ptr<U>;

	class RenderSystem
	{
		public:
			virtual ~RenderSystem() = default;

			// Actions
			virtual void clear()             const = 0;
			virtual void render()            const = 0;
			virtual void pollEvents()        const = 0;
			virtual void swapBuffers()       const = 0;
			virtual int windowShouldClose()  const = 0;

		protected:
			uPtr<Window> m_window = nullptr;
	};

} // GE
