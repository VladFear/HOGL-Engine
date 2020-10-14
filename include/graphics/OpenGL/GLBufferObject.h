#pragma once

#include <GL/glew.h>

#include <graphics/IBufferObject.h>

namespace GE
{

	template <typename DataType>
	class GLBufferObject : public IBufferObject
	{
		public:
			GLBufferObject(GLenum bufferType,
			               size_t size,
			               const DataType data[],
			               GLenum usage) :
				m_bufferType { bufferType },
				m_size { size }
			{
				glGenBuffers(1, &m_id);

				bind();

				glBufferData(m_bufferType, size * sizeof(DataType), data, usage);

				// TODO: Isn't the best solution
				if (bufferType == GL_ARRAY_BUFFER)
					glVertexAttribPointer(0,
					                      size,
					                      GL_FLOAT,
					                      GL_FALSE,
					                      size * sizeof(DataType),
					                      (const void*)0);

				unbind();
			}

			~GLBufferObject()
			{
				glDeleteBuffers(1, &m_id);
			}

			GLBufferObject(const GLBufferObject & other) = delete;
			GLBufferObject & operator=(const GLBufferObject & other) = delete;

			size_t getSize() const
			{
				return m_size;
			}

		protected:
			// Actions
			void bind() const override
			{
				glBindBuffer(m_bufferType, m_id);
			}

			void unbind() const override
			{
				glBindBuffer(m_bufferType, 0);
			}

		protected:
			GLenum m_bufferType;

			GLuint m_id   = 0;
			size_t m_size = 0;
	};

} // GE
