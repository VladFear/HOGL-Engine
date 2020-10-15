#pragma once

#include <forward_list>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "graphics/Shader.h"

namespace GE
{

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	using vec3 = glm::vec3;
	using mat4 = glm::mat4;

	class ShaderProgram
	{
		public:
			ShaderProgram();
			virtual ~ShaderProgram();
			ShaderProgram(const ShaderProgram & other) = delete;
			ShaderProgram(ShaderProgram && other) = delete;
			ShaderProgram & operator=(const ShaderProgram & other) = delete;
			ShaderProgram & operator=(ShaderProgram && other) = delete;

			// Actions
			void attachShader(const Shader & shader);
			void attachShader(sPtr<Shader> shader);
			void attachShader(Shader * shader) = delete;
			void compile();
			void apply() const;
			void unapply() const;
			int getUniformLocation(const std::string & uniform_name) const;
			void getAllUniformLocations();

			// Getters
			uint getId() const;

			// Setters
			void setValidationStrategy(sPtr<IValidationStrategy> validationStrategy);
			void setFloatToUniform(const int location, const float value);
			void setBoolToUniform(const int location, const bool value);
			void setVector3fToUniform(const int location, const vec3 & vector);
			void setMatrixToUniform(const int location, const mat4 & matrix);
			void setTransformMatrix(const mat4 & transformMatrix);
			void setProjectionMatrix(const mat4 & projectionMatrix);
			void setViewMatrix(const mat4 & viewMatrix);

		private:
			void validate() const;

		private:
			std::forward_list<uint> m_shadersIds;
			sPtr<IValidationStrategy> m_validationStrategy;

			uint m_id = 0;

			int m_transformMatrixLocation  = 0;
			int m_projectionMatrixLocation = 0;
			int m_viewMatrixLocation       = 0;
	};

} // GE
