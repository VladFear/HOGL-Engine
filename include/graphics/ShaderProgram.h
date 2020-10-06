#pragma once

#include <forward_list>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <graphics/Shader.h>

class ShaderProgram
{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();
		ShaderProgram(const ShaderProgram & other) = delete;
		ShaderProgram(ShaderProgram && other) = delete;
		ShaderProgram & operator=(const ShaderProgram & other) = delete;
		ShaderProgram & operator=(ShaderProgram && other) = delete;
		void attachShader(const Shader & shader);
		void attachShader(std::shared_ptr<Shader> shader);
		void attachShader(Shader * shader) = delete;
		void setValidationStrategy(std::shared_ptr<IValidationStrategy> validation_strategy);
		void compile();
		unsigned int value() const;
		void apply() const;
		void unapply() const;
		int getUniformLocation(const std::string & uniform_name) const;
		void setFloatToUniform(const int location, const float value);
		void setBoolToUniform(const int location, const bool value);
		void setVector3fToUniform(const int location, const glm::vec3 & vector);
		void setMatrixToUniform(const int location, const glm::mat4 & matrix);
		void setTransformMatrix(const glm::mat4 & transform_matrix);
		void setProjectionMatrix(const glm::mat4 & projection_matrix);
		void setViewMatrix(const glm::mat4 & viewMatrix);
		void getAllUniformLocations();

	private:
		void validate() const;

	private:
		std::forward_list<unsigned int> m_shaders;
		std::shared_ptr<IValidationStrategy> m_validation_strategy;

		unsigned int m_shader;

		int m_transform_matrix_location;
		int m_projection_matrix_location;
		int m_viewMatrixLocation;
};
