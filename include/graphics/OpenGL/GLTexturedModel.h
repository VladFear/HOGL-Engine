#pragma once

#include "core/Memory.h"
#include "graphics/IDrawable.h"
#include "graphics/OpenGL/GLTexture.h"
#include "graphics/Model.h"

namespace GE
{

	class GLTexturedModel final : public IDrawable
	{
		public:
			GLTexturedModel() = delete;
			GLTexturedModel(Shared<Model> model,
			                Shared<GLTexture> texture);

		[[nodiscard]] const Shared<Model>     & getModel()   const;
		[[nodiscard]] const Shared<GLTexture> & getTexture() const;

			void draw() const override;

		private:
			Shared<Model>     m_model   = nullptr;
			Shared<GLTexture> m_texture = nullptr;
	};

} // GE
