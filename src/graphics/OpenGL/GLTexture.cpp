#include "graphics/OpenGL/GLTexture.h"

namespace GE
{

	GLTexture::GLTexture(const path& texturePath)
	{
		const std::string texturePathString = texturePath.native();

		if (!fs::exists(texturePath))
			throw std::invalid_argument("Texture path " + texturePathString + " does not exist.\n");

		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		m_texture = SOIL_load_image(
			texturePath.native().c_str(),
			&m_width,
			&m_height,
			nullptr,
			SOIL_LOAD_RGB);

		if (m_texture)
		{
			glTexImage2D(GL_TEXTURE_2D,
			             0,
			             GL_RGB,
			             m_width,
			             m_height,
			             0,
			             GL_RGB,
			             GL_UNSIGNED_BYTE,
			             m_texture);

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
			throw std::runtime_error("Failed to load texture: " + texturePathString + '\n');

		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(m_texture);
	}

	GLTexture::~GLTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTexture::apply() const
	{
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void GLTexture::unapply() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} // GE
