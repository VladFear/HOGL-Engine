#pragma once

#include <memory>

#include "graphics/Window.h"

namespace GE
{

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
	};

} // GE
