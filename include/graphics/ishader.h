#pragma once

#include <GL/glew.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

class IShader
{
	private:
		void virtual validate() const = 0;

	public:
		virtual ~IShader() {};
		void virtual compile() = 0;
		unsigned int virtual value() const = 0;
};
