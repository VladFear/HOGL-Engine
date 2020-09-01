#pragma once

#include <memory>

#include <GL/glew.h>

#include <graphics/GameObject.h>

class Model : public GameObject
{
	public:
		Model();
		~Model();
		void draw() const override;

	public:
		class ModelBuilder
		{
			public:
				ModelBuilder();
				~ModelBuilder() = default;
				Model * create();
				ModelBuilder & addVertexBuffer(const float positions[],
				                               const unsigned int vertex_count);
				ModelBuilder & addIndexBuffer(const unsigned int indexes[],
				                              const unsigned int indexes_count);

			private:
				void createVAO();
				void createVBO();
				void dataToVBO(const float data[]);
				void dataToInd(const unsigned int data[]);

			private:
				Model * m_model;
		};

	private:
		unsigned int m_vao_id;
		unsigned int m_vbos[2];
		unsigned int m_vertex_count;
		unsigned int m_indexes_count;
};
