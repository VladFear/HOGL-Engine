#pragma once

#include <memory>
#include <vector>

#include <GL/glew.h>

#include "graphics/IDrawable.h"
#include "graphics/OpenGL/GLVertexArrayObject.h"

namespace GE
{
	// Preferable way of creation is via Builder
	class Model : public IDrawable
	{
		public:
			class ModelBuilder;

			Model() = delete;
			~Model();
			Model(const float * vertexPositions,
			      const uint    vertexCount,
			      const uint * indexesData,
			      const uint   indexesCount,
			      const float * textureCoordinates,
			      const uint    textCoordsCount);

			void draw() const override;

		private:
			void storeDataToVBO(const uint attribIndex,
			                    const uint size,
			                    const float * data,
			                    const uint dataCount);
			void storeDataToIndexBuffer(const uint * indexesData,
			                            const uint   indexesCount);


		private:
			std::vector<GLuint> m_vbos;
			GLVertexArrayObject m_vao;
			uint m_indexesCount { 0 };
	};

	class Model::ModelBuilder
	{
		public:
			ModelBuilder & addVertexBuffer(float * vertexPositions,
			                               const uint vertexCount);
			ModelBuilder & addIndexBuffer(uint * indexesData,
			                              const uint indexesCount);
			ModelBuilder & addTextureData(float * textureCoordinates,
			                              const uint textCoordsCount);
			[[nodiscard]] std::shared_ptr<Model> build();

		private:
			float * m_vertexPositions    = nullptr;
			float * m_textureCoordinates = nullptr;
			uint  * m_indexesData        = nullptr;
			uint m_vertexCount     { 0 };
			uint m_indexesCount    { 0 };
			uint m_textCoordsCount { 0 };
	};

} // GE
