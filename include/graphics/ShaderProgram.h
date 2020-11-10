#pragma once

#include <forward_list>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/Memory.h"
#include "graphics/Shader.h"

namespace GE
{

	using vec3 = glm::vec3;
	using mat4 = glm::mat4;

	class ShaderProgram
	{
		public:
			ShaderProgram();
			virtual ~ShaderProgram();

			// Forbid copy semantics
			ShaderProgram(const ShaderProgram & other)             = delete;
			ShaderProgram & operator=(const ShaderProgram & other) = delete;

			// Actions
			void attachShader(const Shader & shader);
			void attachShader(Shared<Shader> shader);
			void attachShader(Shader * shader) = delete;
			void compile();
			void apply() const;
			void unapply() const;
			[[nodiscard]] int getUniformLocation(const std::string & uniformName) const;
			void getAllUniformLocations();

			// Getters
			uint getId() const;

			// Setters
			void setValidationStrategy(Shared<IValidationStrategy> validationStrategy);
			void setFloatToUniform(const int location, const float value);
			void setBoolToUniform(const int location, const bool value);
			void setVector3fToUniform(const int location, const vec3 & vector);
			void setMatrixToUniform(const int location, const mat4 & matrix);
			void setModelMatrix(const mat4 & modelMatrix);
			void setProjectionMatrix(const mat4 & projectionMatrix);
			void setViewMatrix(const mat4 & viewMatrix);

		private:
			void validate() const;

		private:
			std::forward_list<uint> m_shadersIds;
			Shared<IValidationStrategy> m_validationStrategy;

			uint m_id = 0;

			int m_modelMatrixLocation  = 0;
			int m_projectionMatrixLocation = 0;
			int m_viewMatrixLocation       = 0;
	};

} // GE
