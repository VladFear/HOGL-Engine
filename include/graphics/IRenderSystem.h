#pragma once

#include <memory>

#include "graphics/IWindow.h"

namespace GE
{

	class IRenderSystem
	{
		public:
			virtual ~IRenderSystem() = default;

			// Actions
			virtual void clear()             const = 0;
			virtual void render()            const = 0;
			virtual void pollEvents()        const = 0;
			virtual void swapBuffers()       const = 0;
			virtual int  windowShouldClose() const = 0;
	};

} // GE
