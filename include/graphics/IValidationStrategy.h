#pragma once

#include <GL/glew.h>

enum class ValidationPoint : GLenum
{
	COMPILATION = GL_COMPILE_STATUS,
	LINKING = GL_LINK_STATUS
};

class IValidationStrategy
{
	public:
		IValidationStrategy() = default;
		virtual ~IValidationStrategy() = default;
		virtual void validate(const unsigned int shader_id,
		                      const ValidationPoint validation_point) const = 0;
};
