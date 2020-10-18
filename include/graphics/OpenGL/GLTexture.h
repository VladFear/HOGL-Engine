#pragma once

#include <filesystem>
#include <memory>

#include <GL/glew.h>

#include <SOIL2.h>

namespace GE
{

	namespace fs = std::filesystem;
	using path = std::filesystem::path;

	class GLTexture final
	{
		public:
			GLTexture() = delete;
			~GLTexture();
			explicit GLTexture(const path & texturePath);

			void apply() const;
			void unapply() const;

		private:
			GLuint m_textureId { 0 };
			int m_width        { 0 };
			int m_height       { 0 };

			uint8_t * m_texture = nullptr;
	};

} // GE
