#include <graphics/Model.h>

namespace GE
{

	using Builder = Model::ModelBuilder;

	Builder::ModelBuilder()
	{
		m_model = std::make_shared<Model>();
	}

	Builder & Builder::addVertexBuffer(const GLfloat positions[],
	                                   const GLuint vertexCount)
	{
		m_model->m_vao.bind();

		m_model->m_vertexBuffer = std::make_unique<GLBufferObject<GLfloat>>(
			GL_ARRAY_BUFFER,
			vertexCount,
			positions,
			GL_STATIC_DRAW);

		m_model->m_vao.unbind();

		return *this;
	}

	Builder & Builder::addIndexBuffer(const GLuint indexes[],
	                                  const GLuint indexesCount)
	{
		m_model->m_vao.bind();

		m_model->m_indexBuffer = std::make_unique<GLBufferObject<GLuint>>(
			GL_ELEMENT_ARRAY_BUFFER,
			indexesCount,
			indexes,
			GL_STATIC_DRAW);

		m_model->m_vao.unbind();

		return *this;
	}

	void Model::draw() const
	{
		m_vao.bind();

		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, m_indexBuffer->getSize(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);

		m_vao.unbind();
	}

	sPtr<Model> Builder::create()
	{
		return m_model;
	}

} // GE
