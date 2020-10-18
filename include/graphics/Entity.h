#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "graphics/IDrawable.h"
#include "graphics/OpenGL/GLTexturedModel.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Camera.h"

namespace GE
{

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	using vec3 = glm::vec3;
	using mat4 = glm::mat4;

	class Entity : public IDrawable
	{
		public:
			Entity() = default;
			~Entity() = default;

			Entity(sPtr<GLTexturedModel> texturedModel,
			       sPtr<ShaderProgram> shaderProgram);

			Entity(sPtr<GLTexturedModel> texturedModel,
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
			[[nodiscard]] uint getShaderProgramId() const;
			[[nodiscard]] sPtr<GLTexturedModel> getTexturedModel() const;
			[[nodiscard]] sPtr<ShaderProgram>   getShaderProgram() const;
			[[nodiscard]] const vec3 & getPosition()      const noexcept;
			[[nodiscard]] const vec3 & getRotation()      const noexcept;
			[[nodiscard]] const vec3 & getScalingFactor() const noexcept;

		private:
			sPtr<GLTexturedModel> m_texturedModel = nullptr;
			sPtr<ShaderProgram>   m_shaderProgram = nullptr;

			vec3 m_position { 0.f };
			vec3 m_rotation { 0.f };
			vec3 m_scaling  { 1.f };

			uint m_shaderProgramId { 0 };
	};

} // GE
