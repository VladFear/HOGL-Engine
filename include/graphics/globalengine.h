#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <string>
#include <memory>
#include <graphics/model.h>

class engine_init_ex: public std::exception
{
	private:
		std::string what_message;

	public:
		engine_init_ex(const std::string message) : what_message(message)
		{}

	const char* what() const throw()
	{
		return what_message.c_str();
	}
};

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
