#include <Entity.h>

Entity::Entity(std::shared_ptr<Model> model,
               std::shared_ptr<ShaderProgram> shader_program) :
	m_model(model),
	m_shader_program(shader_program)
{
	m_shader_program_id = m_shader_program->value();
}

Entity::Entity(std::shared_ptr<Model> model,
               std::shared_ptr<ShaderProgram> shader_program,
               const glm::vec3 & position,
               const glm::vec3 & rotation,
               const glm::vec3 & scaling) :
	m_model(model),
	m_shader_program(shader_program),
	m_position(position),
	m_rotation(rotation),
	m_scaling(scaling)
{
	m_shader_program_id = m_shader_program->value();
}

Entity::Entity(const Entity & other)
{
		// Free resources
	m_model.reset();
	m_shader_program.reset();

	m_model = other.m_model;
	m_shader_program = other.m_shader_program;

	m_position = other.m_position;
	m_rotation = other.m_rotation;
	m_scaling = other.m_scaling;

	m_shader_program_id = other.m_shader_program_id;
}

Entity::Entity(Entity && other) noexcept
{
	// Free resources
	m_model.reset();
	m_shader_program.reset();

	m_model = other.m_model;
	m_shader_program = other.m_shader_program;

	// Free resources
	other.m_model.reset();
	other.m_shader_program.reset();

	m_position = std::move(other.m_position);
	m_rotation = std::move(other.m_rotation);
	m_scaling = std::move(other.m_scaling);

	m_shader_program_id = std::exchange(other.m_shader_program_id, 0);
}

Entity & Entity::operator=(const Entity & other)
{
	if (&other != this)
	{
		// Free resources
		m_model.reset();
		m_shader_program.reset();

		m_model = other.m_model;
		m_shader_program = other.m_shader_program;

		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scaling = other.m_scaling;

		m_shader_program_id = other.m_shader_program_id;
	}

	return *this;
}

Entity & Entity::operator=(Entity && other) noexcept
{
	if (&other != this)
	{
		// Free resources
		m_model.reset();
		m_shader_program.reset();

		m_model = other.m_model;
		m_shader_program = other.m_shader_program;

		// Free resources
		other.m_model.reset();
		other.m_shader_program.reset();

		m_position = std::move(other.m_position);
		m_rotation = std::move(other.m_rotation);
		m_scaling = std::move(other.m_scaling);

		m_shader_program_id = std::exchange(other.m_shader_program_id, 0);
	}

	return *this;
}

void Entity::setShaderProgram(std::shared_ptr<ShaderProgram> shader_program)
{
	m_shader_program = shader_program;
	m_shader_program_id = m_shader_program->value();
}

unsigned int Entity::getShaderProgramId() const
{
	return m_shader_program_id;
}

std::shared_ptr<Model> Entity::getModel() const
{
	return m_model;
}

std::shared_ptr<ShaderProgram> Entity::getShaderProgram() const
{
	return m_shader_program;
}

void Entity::rotate(const glm::vec3 & rotation) noexcept
{
	// TODO Test this or even change to better solution
	m_rotation.x += rotation.x;
	m_rotation.y += rotation.y;
	m_rotation.z += rotation.z;
}

void Entity::draw() const
{
	glUseProgram(m_shader_program->value());
	m_model->draw();
	glUseProgram(0);
}
