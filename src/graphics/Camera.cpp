#include <graphics/Camera.h>

Camera::Camera(const glm::vec3 & position) : m_position(position)
{

}

Camera::Camera(const glm::vec3 & position,
               const float pitch,
               const float roll,
               const float yaw) :
	m_position(position),
	m_pitch(pitch),
	m_roll(roll),
	m_yaw(yaw)
{

}

float Camera::getPitch() const
{
	return m_pitch;
}

float Camera::getRoll() const
{
	return m_roll;
}

float Camera::getYaw() const
{
	return m_yaw;
}
