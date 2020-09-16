#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <graphics/Model.h>
#include <graphics/ShaderProgram.h>
#include <physics/Transformations.h>

class Entity : public GameObject
{
	public:
		Entity() = default;
		~Entity() = default;

		Entity(std::shared_ptr<Model> model,
		       std::shared_ptr<ShaderProgram> shader_program);

		Entity(std::shared_ptr<Model> model,
		       std::shared_ptr<ShaderProgram> shader_program,
		       const glm::vec3 & position,
		       const glm::vec3 & rotation,
		       const glm::vec3 & scaling);

		Entity(const Entity & other);
		Entity(Entity && other) noexcept;
		Entity & operator=(const Entity & other);
		Entity & operator=(Entity && other) noexcept;

		void setShaderProgram(std::shared_ptr<ShaderProgram> shader_program);
		unsigned int getShaderProgramId() const;
		std::shared_ptr<Model> getModel() const;
		std::shared_ptr<ShaderProgram> getShaderProgram() const;
		void rotate(const glm::vec3 & rotation) noexcept;
		void draw() const override;

	private:
		std::shared_ptr<Model> m_model;
		std::shared_ptr<ShaderProgram> m_shader_program;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scaling;

		unsigned int m_shader_program_id;
};
