#pragma once

#include <string>

#include "graphics/Camera.h"

namespace GE
{

	class IWindow
	{
		public:
			virtual ~IWindow() = default;

			IWindow(const IWindow &)             = delete;
			IWindow & operator=(const IWindow &) = delete;

			// Actions
			virtual void clear()                          const = 0;
			virtual void pollEvents()                     const = 0;
			virtual void swapBuffers()                    const = 0;
			virtual void closeWindow()                    const = 0;
			virtual void setMoveCameraSignal(Shared<Camera> camera) = 0;
			[[nodiscard]] virtual int windowShouldClose() const = 0;

			// Setters
			void setVisibility(const bool visibility)
			{
				m_visibility = visibility;
			}

			// Getters
			[[nodiscard]] uint getWidth()  const
			{
				return m_width;
			}

			[[nodiscard]] uint getHeight() const
			{
				return m_height;
			}

			[[nodiscard]] bool isVisible() const
			{
				return m_visibility;
			}

		protected:
			IWindow(const std::string & title,
			        const uint width,
			        const uint height) :
				m_title  { title },
				m_width  { width },
				m_height { height }
			{ }

		protected:
			std::string m_title;
			uint        m_width;
			uint        m_height;
			bool        m_visibility = true;
	};

} // GE
