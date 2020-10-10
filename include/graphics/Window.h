#pragma once

#include <string>

namespace GE
{

	struct WindowDimensions
	{
		uint width;
		uint height;
	};

	class Window
	{
		public:
			Window() = default;
			Window(const std::string & title,
			       const uint width,
			       const uint height) :
				m_title { title },
				m_dimensions { width, height }
			{  }
			virtual ~Window() = default;

			// Actions
			virtual void swapBuffers() const = 0;
			virtual int windowShouldClose() const = 0;

			// Setters
			void setVisibility(bool visible)
			{
				m_isVisible = visible;
			}

			// Getters
			uint getWidth()  const
			{
				return m_dimensions.width;
			}

			uint getHeight() const
			{
				return m_dimensions.height;
			}

		protected:
			virtual void createWindow() = 0;

		protected:
			std::string m_title = "GlobalEngine";
			WindowDimensions m_dimensions { 1366, 768 };

			bool m_isVisible = true;
	};

} // GE
