#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <graphics/Model.h>
#include <graphics/ShaderProgram.h>
#include <maths/Transformations.h>
#include <graphics/Camera.h>

namespace GE
{

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	using vec3 = glm::vec3;
	using mat4 = glm::mat4;

	class Entity : public GameObject
	{
		public:
			Entity() = default;
			~Entity() = default;

			Entity(sPtr<Model> model,
			       sPtr<ShaderProgram> shaderProgram);

			Entity(sPtr<Model> model,
			       sPtr<ShaderProgram> shaderProgram,
			       const vec3 & position,
			       const vec3 & rotation,
			       const vec3 & scaling);

			Entity(const Entity & other) = delete;
			Entity(Entity && other) noexcept;
			Entity & operator=(const Entity & other) = delete;
			Entity & operator=(Entity && other) noexcept;

			// Actions
			void rotate(const vec3 & rotation) noexcept;
			void scale(const vec3 & scale) noexcept;
			void move(const vec3 & move) noexcept;
			void draw() const override;

			// Setters
			void setShaderProgram(sPtr<ShaderProgram> shaderProgram);
			void setPosition(const vec3 & position) noexcept;
			void setRotation(const vec3 & rotation) noexcept;
			void setScalingFactor(const vec3 & scalingFactor) noexcept;

			// Getters
			unsigned int getShaderProgramId() const;
			sPtr<Model> getModel() const;
			sPtr<ShaderProgram> getShaderProgram() const;
			const vec3 & getPosition() const noexcept;
			const vec3 & getRotation() const noexcept;
			const vec3 & getScalingFactor() const noexcept;

		private:
			sPtr<Model> m_model = nullptr;
			sPtr<ShaderProgram> m_shaderProgram = nullptr;

			mat4 m_projectionMatrix { 1.0f };
			vec3 m_position { 0.f };
			vec3 m_rotation { 0.f };
			vec3 m_scaling  { 1.f };

			unsigned int m_shaderProgramId { 0 };
	};

} // GE
