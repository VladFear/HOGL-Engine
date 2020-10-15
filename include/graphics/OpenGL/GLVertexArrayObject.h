#pragma once

#include <GL/glew.h>

namespace GE
{

	class GLVertexArrayObject final
	{
		public:
			GLVertexArrayObject();
			~GLVertexArrayObject();

		// Actions
		void bind()   const;
		void unbind() const;

		private:
			GLuint m_id = 0;
	};

} // GE
