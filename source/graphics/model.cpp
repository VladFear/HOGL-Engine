#include <graphics/model.h>

Model::Model()
{
	createVAO();
	createVBO();
}

Model::Model(float positions[], unsigned int _vertex_count,
		unsigned int indexes[], unsigned int _indexes_count)
{
	createVAO();
	createVBO();
	vertex_count = _vertex_count;
	indexes_count = _indexes_count;

	glBindVertexArray(vao_id);
	dataToInd(indexes);
	dataToVBO(positions);
	glBindVertexArray(0);
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vao_id);
	glDeleteBuffers(2, vbos);
}

void Model::createVAO()
{
	glGenVertexArrays(1, &vao_id);
}

void Model::createVBO()
{
	glGenBuffers(2, vbos);
}

void Model::dataToVBO(float data[])
{
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::addVertexBuffer(float positions[], unsigned int _vertex_count)
{
	vertex_count = _vertex_count;
	glBindVertexArray(vao_id);
	dataToVBO(positions);
	glBindVertexArray(0);
}

void Model::addIndexBuffer(unsigned int indexes[], unsigned int _indexes_count)
{
	indexes_count = _indexes_count;
	glBindVertexArray(vao_id);
	dataToInd(indexes);
	glBindVertexArray(0);
}

void Model::dataToInd(unsigned int data[])
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
