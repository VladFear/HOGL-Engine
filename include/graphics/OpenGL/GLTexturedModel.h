#pragma once

#include <memory>

#include "graphics/IDrawable.h"
#include "graphics/OpenGL/GLTexture.h"
#include "graphics/Model.h"

namespace GE
{

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	class GLTexturedModel final : public IDrawable
	{
		public:
			GLTexturedModel() = delete;
			GLTexturedModel(sPtr<Model> model,
			                sPtr<GLTexture> texture);

		[[nodiscard]] const sPtr<Model>     & getModel()   const;
		[[nodiscard]] const sPtr<GLTexture> & getTexture() const;

			void draw() const override;

		private:
			sPtr<Model>     m_model   = nullptr;
			sPtr<GLTexture> m_texture = nullptr;
	};

} // GE
