#pragma once

#include <GL/glew.h>

#include <graphics/igameobject.h>

class Model : public IGameObject
{
	private:
		unsigned int vao_id;
		unsigned int vbos[2];
		unsigned int vertex_count;
		unsigned int indexes_count;

	private:
		void createVAO();
		void createVBO();
		void dataToVBO(float data[]);
		void dataToInd(unsigned int data[]);

	public:
		Model();
		Model(float positions[], unsigned int _vertex_count,
			unsigned int indexes[], unsigned int size);
		virtual ~Model();
		void addVertexBuffer(float positions[], unsigned int _vertex_count);
		void addIndexBuffer(unsigned int indexes[], unsigned int _indexes_count);
		void draw() const override;
};
