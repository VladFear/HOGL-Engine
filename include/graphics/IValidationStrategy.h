#pragma once

#include <GL/glew.h>

namespace GE
{

	enum class ValidationPoint : GLenum
	{
		Compilation = GL_COMPILE_STATUS,
		Linking = GL_LINK_STATUS
	};

	class IValidationStrategy
	{
		public:
			IValidationStrategy() = default;
			virtual ~IValidationStrategy() = default;
			virtual void validate(const uint id,
			                      ValidationPoint validationPoint) const = 0;
	};

} // GE
