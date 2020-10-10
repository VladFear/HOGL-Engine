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
			~Camera() = default;

			// Getters
			float getPitch() const;
			float getRoll() const;
			float getYaw() const;

		private:
			vec3 m_position { 0.0f };

			float m_pitch = 0.0f;
			float m_roll  = 0.0f;
			float m_yaw   = 0.0f;
	};

} // GE
