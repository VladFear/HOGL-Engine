#include "Entity.h"

namespace GE
{

	Entity::Entity(sPtr<Model> model,
	               sPtr<ShaderProgram> shaderProgram) :
		m_model { model },
		m_shaderProgram { shaderProgram }
	{
		m_shaderProgramId = m_shaderProgram->getId();
		m_projectionMatrix = createProjectionMatrix();
	}

	Entity::Entity(sPtr<Model> model,
	               sPtr<ShaderProgram> shaderProgram,
	               const vec3 & position,
	               const vec3 & rotation,
	               const vec3 & scaling) :
		m_model         { model },
		m_shaderProgram { shaderProgram },
		m_position      { position },
		m_rotation      { rotation },
		m_scaling       { scaling }
	{
		m_shaderProgramId = m_shaderProgram->getId();
		m_projectionMatrix = createProjectionMatrix();
	}

	Entity::Entity(Entity && other) noexcept
	{
		// Free resources
		m_model.reset();
		m_shaderProgram.reset();

		m_model = other.m_model;
		m_shaderProgram = other.m_shaderProgram;

		// Free resources
		other.m_model.reset();
		other.m_shaderProgram.reset();

		m_position = std::move(other.m_position);
		m_rotation = std::move(other.m_rotation);
		m_scaling  = std::move(other.m_scaling);

		m_shaderProgramId = std::exchange(other.m_shaderProgramId, 0);
	}

	Entity & Entity::operator=(Entity && other) noexcept
	{
		if (&other != this)
		{
			// Free resources
			m_model.reset();
			m_shaderProgram.reset();

			m_model = other.m_model;
			m_shaderProgram = other.m_shaderProgram;

			// Free resources
			other.m_model.reset();
			other.m_shaderProgram.reset();

			m_position = std::move(other.m_position);
			m_rotation = std::move(other.m_rotation);
			m_scaling  = std::move(other.m_scaling);

			m_shaderProgramId = std::exchange(other.m_shaderProgramId, 0);
		}

		return *this;
	}

	void Entity::setShaderProgram(sPtr<ShaderProgram> shaderProgram)
	{
		m_shaderProgram = shaderProgram;
		m_shaderProgramId = m_shaderProgram->getId();
	}

	unsigned int Entity::getShaderProgramId() const
	{
		return m_shaderProgramId;
	}

	sPtr<Model> Entity::getModel() const
	{
		return m_model;
	}

	sPtr<ShaderProgram> Entity::getShaderProgram() const
	{
		return m_shaderProgram;
	}

	void Entity::draw() const
	{
		m_shaderProgram->apply();

		mat4 transformMatrix = createTransformationMatrix(m_position,
		                                                  m_rotation,
		                                                  m_scaling);

		m_shaderProgram->setTransformMatrix(transformMatrix);
		// TODO: Shouldn't be loaded on every iteration
		m_shaderProgram->setProjectionMatrix(m_projectionMatrix);

		m_shaderProgram->setViewMatrix(createViewMatrix(vec3(0.0f, 0.0f, 0.0001f),
		                                                vec3(0.0f),
		                                                vec3(0.0f, 1.0f, 0.0f)));

		m_model->draw();

		m_shaderProgram->unapply();
	}

	void Entity::rotate(const vec3 & rotation) noexcept
	{
		m_rotation += rotation;
	}

	void Entity::scale(const vec3 & scale) noexcept
	{
		m_scaling *= scale;
	}

	void Entity::move(const vec3 & move) noexcept
	{
		m_position += move;
	}

	const vec3 & Entity::getPosition() const noexcept
	{
		return m_position;
	}

	const vec3 & Entity::getRotation() const noexcept
	{
		return m_rotation;
	}

	const vec3 & Entity::getScalingFactor() const noexcept
	{
		return m_scaling;
	}

	void Entity::setPosition(const vec3 & position) noexcept
	{
		m_position = position;
	}

	void Entity::setRotation(const vec3 & rotation) noexcept
	{
		m_rotation = rotation;
	}

	void Entity::setScalingFactor(const vec3 & scalingFactor) noexcept
	{
		m_scaling = scalingFactor;
	}

} // GE
