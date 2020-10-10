#include <graphics/Model.h>

namespace GE
{

	using Builder = Model::ModelBuilder;

	Model::Model()
	{
		createVAO();
		createVBO();
	}

	Builder::ModelBuilder()
	{
		m_model = std::make_shared<Model>();
	}

	Model::~Model()
	{
		glDeleteVertexArrays(1, &m_vaoId);
		glDeleteBuffers(2, m_vbos);
	}

	void Model::createVAO()
	{
		glGenVertexArrays(1, &m_vaoId);
	}

	void Model::createVBO()
	{
		glGenBuffers(2, m_vbos);
	}

	void Builder::dataToVBO(const float data[])
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, m_model->m_vertexCount * sizeof(float), data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Builder & Builder::addVertexBuffer(const float positions[],
	                                   uint vertexCount)
	{
		m_model->m_vertexCount = vertexCount;
		glBindVertexArray(m_model->m_vaoId);
		dataToVBO(positions);
		glBindVertexArray(0);

		return *this;
	}

	Builder & Builder::addIndexBuffer(const uint indexes[],
	                                  uint indexesCount)
	{
		m_model->m_indexesCount = indexesCount;
		glBindVertexArray(m_model->m_vaoId);
		dataToInd(indexes);
		glBindVertexArray(0);

		return *this;
	}

	void Builder::dataToInd(const uint data[])
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model->m_indexesCount * sizeof(uint), data, GL_STATIC_DRAW);
	}

	void Model::draw() const
	{
		glBindVertexArray(m_vaoId);
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, m_indexesCount, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	sPtr<Model> Builder::create()
	{
		return m_model;
	}

} // GE
