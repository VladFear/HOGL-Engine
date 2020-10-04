#pragma once

#include <string>

struct WindowDimensions
{
	unsigned int width;
	unsigned int height;
};

class Window
{
	public:
		Window() = default;
		Window(const std::string & title,
		       unsigned int width,
		       unsigned int height) :
		m_title(title),
		m_dimensions { width, height }
		{  }

		virtual ~Window() = default;

		virtual void clear() const = 0;
		virtual void swapBuffers() const = 0;
		virtual int windowShouldClose() const = 0;
		unsigned int getWidth()  const { return m_dimensions.width;  };
		unsigned int getHeight() const { return m_dimensions.height; };

	protected:
		virtual void createWindow() = 0;

	protected:
		std::string m_title = "GlobalEngine";
		WindowDimensions m_dimensions { 1366, 768 };
};
