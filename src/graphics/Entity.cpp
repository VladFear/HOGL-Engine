#include "graphics/Entity.h"

namespace GE
{

	Entity::Entity(sPtr<GLTexturedModel> texturedModel,
	               sPtr<ShaderProgram> shaderProgram) :
		m_texturedModel { texturedModel },
		m_shaderProgram { shaderProgram }
	{
		m_shaderProgramId = m_shaderProgram->getId();
	}

	Entity::Entity(sPtr<GLTexturedModel> texturedModel,
	               sPtr<ShaderProgram> shaderProgram,
	               const vec3 & position,
	               const vec3 & rotation,
	               const vec3 & scaling) :
		m_texturedModel { texturedModel },
		m_shaderProgram { shaderProgram },
		m_position      { position },
		m_rotation      { rotation },
		m_scaling       { scaling }
	{
		m_shaderProgramId = m_shaderProgram->getId();
	}

	Entity::Entity(Entity && other) noexcept
	{
		// Free resources
		m_texturedModel.reset();
		m_shaderProgram.reset();

		m_texturedModel = other.m_texturedModel;
		m_shaderProgram = other.m_shaderProgram;

		// Free resources
		other.m_texturedModel.reset();
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
			m_texturedModel.reset();
			m_shaderProgram.reset();

			m_texturedModel = other.m_texturedModel;
			m_shaderProgram = other.m_shaderProgram;

			// Free resources
			other.m_texturedModel.reset();
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

	sPtr<GLTexturedModel> Entity::getTexturedModel() const
	{
		return m_texturedModel;
	}

	sPtr<ShaderProgram> Entity::getShaderProgram() const
	{
		return m_shaderProgram;
	}

	void Entity::draw() const
	{
		m_shaderProgram->apply();
		m_texturedModel->draw();
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
