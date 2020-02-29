#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <string>
#include <memory>
#include <graphics/model.h>

class GlobalEngine final
{
	private:
		GLFWwindow* _window = nullptr;
		unsigned int _width = 640;
		unsigned int _height = 480;

	public:
		GlobalEngine();
		~GlobalEngine();
		void initialize();
		unsigned int windowWidth() const { return _width; }
		unsigned int windowHeight() const { return _height; }
		GLFWwindow* window() { return _window; }
		void pollEvents() const;
		void swapBuffers() const;
		void render(const Model& model) const;
		void clear() const;
};
