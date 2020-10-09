#pragma once

#include <graphics/IValidationStrategy.h>

class ValidationDefaultStrategy : public IValidationStrategy
{
	public:
		void validate(const unsigned int shader_id,
		              const ValidationPoint validation_point) const override
		{
			int success = 0;

			glGetProgramiv(shader_id, static_cast<GLenum>(validation_point), &success);
			if (!success)
			{
				/* Pull the error message */
				char info_log[1024];
				glGetProgramInfoLog(shader_id, sizeof(info_log), nullptr, info_log);

				throw std::runtime_error(std::string(info_log) + '\n');
			}
		}
};
