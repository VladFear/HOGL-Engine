#pragma once

#include <memory>

#include <GL/glew.h>

#include "graphics/GameObject.h"
#include "graphics/OpenGL/GLVertexArrayObject.h"

namespace GE
{

	template <typename S>
	using sPtr = std::shared_ptr<S>;

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
					sPtr<Model> create();
					ModelBuilder & addVertexBuffer(const float positions[],
					                               const uint vertexCount);
					ModelBuilder & addIndexBuffer(const uint indexes[],
					                              const uint indexesCount);

					void dataToVBO(const float data[]);
					void dataToInd(const uint data[]);

				private:
					sPtr<Model> m_model;
			};

		private:
			void createVBO();

		private:
			GLVertexArrayObject m_vao;
			uint m_vbos[2];
			uint m_vertexCount;
			uint m_indexesCount;
	};

} // GE
