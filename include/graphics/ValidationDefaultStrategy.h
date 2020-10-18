#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "graphics/IValidationStrategy.h"

namespace GE
{

	class ValidationDefaultStrategy : public IValidationStrategy
	{
		public:
			void validate(const uint id,
			              const ValidationPoint validationPoint) override
			{
				GLint operationSuccessful;

				glGetProgramiv(id, static_cast<GLenum>(validationPoint), &operationSuccessful);

				if (operationSuccessful == GL_FALSE)
				{
					// Figure out the maximum size of buffer
					GLint maxLength = 0;
					glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

					// Pull the error message
					m_infoLog.reserve(maxLength);
					glGetProgramInfoLog(id, maxLength, &maxLength, &m_infoLog[0]);

					// Print information about error
					std::copy(std::begin(m_infoLog), std::end(m_infoLog), std::ostream_iterator<GLchar>(std::cerr));
				}
			}

		private:
			std::vector<GLchar> m_infoLog;
	};

} // GE
