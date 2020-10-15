#include "graphics/Model.h"

namespace GE
{

	using Builder = Model::ModelBuilder;

	Model::Model()
	{
		createVBO();
	}

	Builder::ModelBuilder()
	{
		m_model = std::make_shared<Model>();
	}

	Model::~Model()
	{
		glDeleteBuffers(2, m_vbos);
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
		m_model->m_vao.bind();
		dataToVBO(positions);
		m_model->m_vao.unbind();

		return *this;
	}

	Builder & Builder::addIndexBuffer(const uint indexes[],
	                                  uint indexesCount)
	{
		m_model->m_indexesCount = indexesCount;
		m_model->m_vao.bind();
		dataToInd(indexes);
		m_model->m_vao.unbind();

		return *this;
	}

	void Builder::dataToInd(const uint data[])
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model->m_indexesCount * sizeof(uint), data, GL_STATIC_DRAW);
	}

	void Model::draw() const
	{
		m_vao.bind();
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, m_indexesCount, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		m_vao.unbind();
	}

	sPtr<Model> Builder::create()
	{
		return m_model;
	}

} // GE
