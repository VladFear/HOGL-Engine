#pragma once

#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <memory>
#include <filesystem>

#include <GL/glew.h>

#include "graphics/ValidationDefaultStrategy.h"

namespace GE
{

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	namespace fs = std::filesystem;
	using path = std::filesystem::path;

	class Shader
	{
		public:
			Shader() = default;
			virtual ~Shader() = default;

			// Getters
			uint getId() const;

		public:
			class ShaderBuilder
			{
				public:
					ShaderBuilder();
					~ShaderBuilder() = default;
					ShaderBuilder & setSource(const path & shaderPath);
					ShaderBuilder & setValidationStrategy(sPtr<IValidationStrategy> validationStrategy);
					sPtr<Shader> create(GLenum shaderType);

				private:
					void validate() const;
					void createSourceStringFromFile(std::ifstream & file);

				private:
					sPtr<Shader> m_shaderPtr;
					sPtr<IValidationStrategy> m_validationStrategy;
			};

		protected:
			std::string m_source;
			uint m_id;
	};

} // GE
