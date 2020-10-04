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

		// Actions
		void rotate(const glm::vec3 & rotation) noexcept;
		void scale(const glm::vec3 & scale) noexcept;
		void move(const glm::vec3 & move) noexcept;
		void draw() const override;

		// Setters
		void setShaderProgram(std::shared_ptr<ShaderProgram> shader_program);
		void setPosition(const glm::vec3 & position) noexcept;
		void setRotation(const glm::vec3 & rotation) noexcept;
		void setScalingFactor(const glm::vec3 & scaling_factor) noexcept;

		// Getters
		unsigned int getShaderProgramId() const;
		std::shared_ptr<Model> getModel() const;
		std::shared_ptr<ShaderProgram> getShaderProgram() const;
		const glm::vec3 & getPosition() const noexcept;
		const glm::vec3 & getRotation() const noexcept;
		const glm::vec3 & getScalingFactor() const noexcept;

	private:
		std::shared_ptr<Model> m_model = nullptr;
		std::shared_ptr<ShaderProgram> m_shader_program = nullptr;

		glm::mat4 m_projection_matrix{1.0f};

		glm::vec3 m_position{0.f};
		glm::vec3 m_rotation{0.f};
		glm::vec3 m_scaling{1.f};

		unsigned int m_shader_program_id = 0;
};
