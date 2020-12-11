#pragma once

#include <vector>
#include <filesystem>
#include <fstream>
#include <exception>
#include <string>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include "graphics/Model.h"

namespace GE
{

	using path = std::filesystem::path;

	class OBJParser final
	{
		public:
			static void parseObj(const path & objPath);

		private:
			static void parseObjImpl(const path & objPath);
			static void processVertex(const std::vector<std::string> & vertexStrings,
			                          const std::vector<std::tuple<float,float,float>> & vertexVector,
			                          const std::vector<std::pair<float,float>> & textureVector,
			                          const std::vector<std::tuple<float,float,float>> & normalsVector,
			                          float * vertexArray,
			                          float * textureArrray,
			                          uint  * indexesArray);
	};

} // GE