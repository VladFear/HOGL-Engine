#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <string>
#include <memory>
#include <iostream>

#include <graphics/OpenGLWindow.h>

enum class EngineAPI: int8_t
{
	UNDEFINED = -1,
	OpenGL = 0,
	Vulkan = 1,
};

class RenderEngine
{
	public:
		RenderEngine(EngineAPI api);
		virtual ~RenderEngine();
		void render() const;
		void pollEvents() const;
		void swapBuffers() const;
		void clear() const;
		int windowShouldClose() const;

	private:
		void initOpenGL();
		void initGLFW() const;
		void initGLEW() const;

	private:
		std::unique_ptr<Window> m_window = nullptr;
		EngineAPI m_current_api = EngineAPI::UNDEFINED;
};
