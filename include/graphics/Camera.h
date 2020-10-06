#pragma once

#include <glm/glm.hpp>

class Camera
{
	public:
		Camera() = default;
		explicit Camera(const glm::vec3 & position);
		Camera(const glm::vec3 & position,
		       const float pith,
		       const float roll,
		       const float yaw);
		~Camera() = default;

		// Getters
		float getPitch() const;
		float getRoll() const;
		float getYaw() const;

	private:
		glm::vec3 m_position { 0.0f };

		float m_pitch = 0.0f;
		float m_roll  = 0.0f;
		float m_yaw   = 0.0f;
};
