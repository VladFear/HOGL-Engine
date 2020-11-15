#pragma once

#include <glm/glm.hpp>

namespace GE
{

	using vec3 = glm::vec3;

	class Camera
	{
		public:
			Camera() = default;
			explicit Camera(const vec3 & position);
			Camera(const vec3 & position,
			       const float pith,
			       const float roll,
			       const float yaw);

			// Actions
			void move(const vec3 & position);
			void moveTo(const vec3 & position);

			// Getters
			[[nodiscard]] float getPitch() const;
			[[nodiscard]] float getRoll() const;
			[[nodiscard]] float getYaw() const;
			[[nodiscard]] const vec3 & getPosition() const;

		private:
			vec3 m_position { 0.0f };

			float m_pitch = 0.0f;
			float m_roll  = 0.0f;
			float m_yaw   = 0.0f;
	};

} // GE
