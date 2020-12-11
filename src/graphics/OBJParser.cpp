#include "graphics/OBJParser.h"

namespace GE
{

    Unique<Model> OBJParser::parseObj(const path & objPath)
    {
        if (!std::filesystem::exists(objPath))
            throw std::runtime_error("The .obj filepath \"" + objPath.native() + "\" does not exist!");

        return parseObjImpl(objPath);
    }

	Unique<Model> OBJParser::parseObjImpl(const path & objPath)
    {
        std::ifstream file(objPath.native());

        if (!file.is_open())
            throw std::runtime_error(".obj file isn't open!");

        using Vertex3f = std::tuple<float, float, float>;
        using Normal   = std::tuple<float, float, float>;
        using Texture  = std::pair<float, float>;

        std::deque<Vertex3f> vertexDeque;
        std::deque<Normal> normalDeque;
        std::deque<Texture> textureDeque;
        std::deque<uint> indexesDeque;

        std::string line;
        std::string prefix;
        std::stringstream ss;

        float * vertexArray  = nullptr;
        float * textureArray = nullptr;
        float * normalArray  = nullptr;
        uint  * indexesArray = nullptr;

        float x = 0;
        float y = 0;
        float z = 0;
        float u = 0;
        float v = 0;

        while (std::getline(file, line))
        {
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "v")
            {
                ss >> x >> y >> z;
                vertexDeque.push_back(std::make_tuple(x, y, z));
            }
            else if (prefix == "vt")
            {
                ss >> u >> v;
                textureDeque.push_back(std::make_pair(u, v));
            }
            else if (prefix == "vn")
            {
                ss >> x >> y >> z;
                normalDeque.push_back(std::make_tuple(x, y, z));
            }
            else if (prefix == "f")
                break;
        }

        const size_t SIZE = vertexDeque.size();
        vertexArray = new float[SIZE * 3];
        textureArray = new float[SIZE * 2];
        normalArray = new float[SIZE * 3];

        std::string vertex1, vertex2, vertex3;
        while (std::getline(file, line))
        {
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix != "f") continue;

            ss >> vertex1 >> vertex2 >> vertex3;

            processVertex(vertex1, normalDeque, textureDeque,
                          indexesDeque, normalArray, textureArray);

            processVertex(vertex2, normalDeque, textureDeque,
                          indexesDeque, normalArray, textureArray);

            processVertex(vertex3, normalDeque, textureDeque,
                          indexesDeque, normalArray, textureArray);
        }

        indexesArray = new uint[indexesDeque.size()];

        for (size_t i = 0; i < vertexDeque.size(); i++)
        {
            auto [x, y, z] = vertexDeque[i];

            vertexArray[i * 3] = x;
            vertexArray[i * 3 + 1] = y;
            vertexArray[i * 3 + 2] = z;
        }

        for (size_t i = 0; i < indexesDeque.size(); i++)
            indexesArray[i] = indexesDeque[i];

        return Model::ModelBuilder().addVertexBuffer(vertexArray, SIZE)
                                    .addIndexBuffer(indexesArray, indexesDeque.size())
                                    .addTextureData(textureArray, SIZE)
                                    .build();
    }

	void OBJParser::processVertex(const std::string & vertexString,
	                              const std::deque<std::tuple<float, float, float>> & normalDeque,
	                              const std::deque<std::pair<float, float>> & textureDeque,
	                              std::deque<uint> & indexesDeque,
	                              float * normalArray,
	                              float * textureArray)
	{
		std::vector<std::string> vertexes;
		boost::split(vertexes, vertexString, boost::is_any_of("/"), boost::algorithm::token_compress_on);

		std::stringstream ss;

		ss << vertexes[0] << ' ' << vertexes[1] << ' ' << vertexes[2];
		uint v, t, n;

		ss >> v >> t >> n;

		v -= 1;

		indexesDeque.push_back(v);
		textureArray[v * 2] = textureDeque[t - 1].first;
		textureArray[v * 2 + 1] = 1 - textureDeque[t - 1].second;

		auto [x, y, z] = normalDeque[n - 1];
		normalArray[v * 3] = x;
		normalArray[v * 3 + 1] = y;
		normalArray[v * 3 + 2] = z;
	}

} // GE
