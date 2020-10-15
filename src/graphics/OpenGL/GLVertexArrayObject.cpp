#include "graphics/OpenGL/GLVertexArrayObject.h"

namespace GE
{

	GLVertexArrayObject::GLVertexArrayObject()
	{
		glGenVertexArrays(1, &m_id);
	}

	GLVertexArrayObject::~GLVertexArrayObject()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void GLVertexArrayObject::bind()   const
	{
		glBindVertexArray(m_id);
	}

	void GLVertexArrayObject::unbind() const
	{
		glBindVertexArray(0);
	}

} // GE
