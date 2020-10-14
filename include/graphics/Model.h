#pragma once

#include <memory>

#include <GL/glew.h>

#include <graphics/GameObject.h>
#include <graphics/OpenGL/GLVertexArrayObject.h>
#include <graphics/OpenGL/GLBufferObject.h>

namespace GE
{

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	template <typename U>
	using uPtr = std::unique_ptr<U>;

	class Model : public GameObject
	{
		public:
			Model() = default;
			~Model() = default;
			void draw() const override;

		public:
			class ModelBuilder
			{
				public:
					ModelBuilder();
					~ModelBuilder() = default;
					sPtr<Model> create();
					ModelBuilder & addVertexBuffer(const GLfloat positions[],
					                               const GLuint vertexCount);
					ModelBuilder & addIndexBuffer(const GLuint indexes[],
					                              const GLuint indexesCount);

				private:
					sPtr<Model> m_model;
			};

		private:
			GLVertexArrayObject m_vao;
			uPtr<GLBufferObject<GLfloat>> m_vertexBuffer = nullptr;
			uPtr<GLBufferObject<GLuint>>  m_indexBuffer  = nullptr;
	};

} // GE
