#pragma once

#include "graphics/IValidationStrategy.h"

namespace GE
{

	class ValidationDefaultStrategy : public IValidationStrategy
	{
		public:
			void validate(const uint id,
			              const ValidationPoint validationPoint) const override
			{
				int success = 0;

				glGetProgramiv(id, static_cast<GLenum>(validationPoint), &success);

				if (!success)
				{
					/* Pull the error message */
					char infoLog[1024];
					glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);

					throw std::runtime_error(std::string(infoLog) + '\n');
				}
			}
	};

} // GE
