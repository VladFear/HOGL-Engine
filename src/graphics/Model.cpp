#include "graphics/Model.h"

namespace GE
{

	using Builder = Model::ModelBuilder;

	// Model class

	Model::Model(const float * vertexPositions,
	             const uint    vertexCount,
	             const uint * indexesData,
	             const uint   indexesCount,
	             const float * textureCoordinates,
	             const uint    textCoordsCount)
	{
		m_vbos.reserve(5);

		m_vao.bind();

		// Store vertex attributes
		storeDataToVBO(0, 3, vertexPositions, vertexCount);
		storeDataToIndexBuffer(indexesData, indexesCount);
		storeDataToVBO(1, 2, textureCoordinates, textCoordsCount);

		// Save needed data
		m_indexesCount = indexesCount;

		m_vao.unbind();
	}

	Model::~Model()
	{
		for (auto vbo : m_vbos)
			glDeleteBuffers(1, &vbo);
	}

	void Model::storeDataToIndexBuffer(const uint * indexesData,
	                                   const uint   indexesCount)
	{
		// Create and save new vertex buffer
		GLuint newVbo = 0;
		glGenBuffers(1, &newVbo);
		m_vbos.push_back(newVbo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newVbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexesCount * sizeof(uint), indexesData, GL_STATIC_DRAW);
	}

	void Model::storeDataToVBO(const uint attribIndex,
	                           const uint size,
	                           const float * data,
	                           const uint dataCount)
	{
		// Create and save new vertex buffer
		GLuint newVbo = 0;
		glGenBuffers(1, &newVbo);
		m_vbos.push_back(newVbo);

		glBindBuffer(GL_ARRAY_BUFFER, newVbo);
		glBufferData(GL_ARRAY_BUFFER, dataCount * sizeof(float), data, GL_STATIC_DRAW);
		glVertexAttribPointer(attribIndex, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (const void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Model::draw() const
	{
		m_vao.bind();

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawElements(GL_TRIANGLES, m_indexesCount, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		m_vao.unbind();
	}

	// ModelBuilder class

	Builder & Builder::addVertexBuffer(float * vertexPositions,
	                                   const uint vertexCount)
	{
		m_vertexPositions = vertexPositions;
		m_vertexCount = vertexCount;

		return *this;
	}

	Builder & Builder::addIndexBuffer(uint * indexesData,
	                                  const uint indexesCount)
	{
		m_indexesData = indexesData;
		m_indexesCount = indexesCount;

		return *this;
	}

	Builder & Builder::addTextureData(float * textureCoordinates,
	                                  const uint textCoordsCount)
	{
		m_textureCoordinates = textureCoordinates;
		m_textCoordsCount = textCoordsCount;

		return *this;
	}

	std::shared_ptr<Model> Builder::build()
	{
		return std::make_shared<Model>(
			m_vertexPositions,
			m_vertexCount,
			m_indexesData,
			m_indexesCount,
			m_textureCoordinates,
			m_textCoordsCount);
	}

} // GE
