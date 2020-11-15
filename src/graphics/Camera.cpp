#include "graphics/Camera.h"

namespace GE
{

	Camera::Camera(const vec3 & position) : m_position { position }
	{

	}

	Camera::Camera(const vec3 & position,
	               const float pitch,
	               const float roll,
	               const float yaw) :
		m_position { position },
		m_pitch    { pitch },
		m_roll     { roll },
		m_yaw      { yaw }
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

	const vec3 & Camera::getPosition() const
	{
		return m_position;
	}

	void Camera::move(const vec3 & position)
	{
		m_position += position;
	}

	void Camera::moveTo(const vec3 & position)
	{
		m_position = position;
	}

} // GE
