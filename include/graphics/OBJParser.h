#pragma once

#include <deque>
#include <filesystem>
#include <fstream>
#include <exception>
#include <string>
#include <iostream>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include "core/Memory.h"
#include "graphics/Model.h"

namespace GE
{

	using path = std::filesystem::path;

	class OBJParser final
	{
		public:
			static Unique<Model> parseObj(const path & objPath);

		private:
			static Unique<Model> parseObjImpl(const path & objPath);
			static void processVertex(const std::string & vertexString,
			                          const std::deque<std::tuple<float, float, float>> & normalDeque,
			                          const std::deque<std::pair<float, float>> & textureDeque,
			                          std::deque<uint> & indexesDeque,
			                          float * normalArray,
			                          float * textureArray);
	};

} // GE