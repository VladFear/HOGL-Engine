#include "graphics/OBJParser.h"

namespace GE
{

    void OBJParser::parseObj(const path & objPath)
    {
        if (!std::filesystem::exists(objPath))
            throw std::runtime_error("The .obj filepath \"" + objPath.native() + "\" does not exist!");

        parseObjImpl(objPath);
    }

	void OBJParser::parseObjImpl(const path & objPath)
    {
        std::ifstream file(objPath.native());

        if (!file.is_open())
            throw std::runtime_error(".obj file isn't open!");

        using VertexCoordinates = std::tuple<float, float, float>;
        using Normals = std::tuple<float, float, float>;
        using TextureUV = std::pair<float, float>;
        using Indexes = uint;

        std::vector<VertexCoordinates> vertexCoordinates;
        std::vector<TextureUV> textureUV;
        std::vector<Normals> normals;
        std::vector<Indexes> indexesData;

        std::string line;
        std::vector<std::string> tokens;

        float * vertexCoordinatesArray = nullptr;
        float * textureCoordinatesArray = nullptr;
        [[maybe_unused]] uint  * indexesArray = nullptr;

        while (std::getline(file, line))
        {
            boost::split(tokens, line, boost::is_any_of(" "), boost::algorithm::token_compress_on);

            try
            {
                if (tokens[0] == "v")
                {
                    float x = std::stof(tokens[1]);
                    float y = std::stof(tokens[2]);
                    float z = std::stof(tokens[3]);

                    VertexCoordinates v = std::make_tuple(x, y, z);
                    vertexCoordinates.push_back(v);
                }
                else if (tokens[0] == "vt")
                {
                    float u = std::stof(tokens[1]);
                    float v = std::stof(tokens[2]);

                    TextureUV vt = std::make_pair(u, v);
                    textureUV.push_back(vt);
                }
                if (tokens[0] == "vn")
                {
                    float x = std::stof(tokens[1]);
                    float y = std::stof(tokens[2]);
                    float z = std::stof(tokens[3]);

                    Normals vn = std::make_tuple(x, y, z);
                    normals.push_back(vn);
                }
                else if (tokens[0] == "f")
                {
                    const size_t VERTICES_ARRAY_SIZE = vertexCoordinates.size() * 3;
                    vertexCoordinatesArray = new float[VERTICES_ARRAY_SIZE];

                    const size_t TEXTURES_ARRAY_SIZE = textureUV.size() * 2;
                    textureCoordinatesArray = new float[TEXTURES_ARRAY_SIZE];

                    if (vertexCoordinatesArray == nullptr or textureCoordinatesArray == nullptr)
                        std::cout << "SUKA\n";
            
                    break;
                }
                else
                    continue;
            }
            catch (const std::invalid_argument & e)
            {
                std::cerr << e.what() << '\n';
            }
            catch (const std::out_of_range & e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        while (std::getline(file, line))
        {
            boost::split(tokens, line, boost::is_any_of(" "), boost::algorithm::token_compress_on);

            try
            {
                if (tokens[0] == "f")
                {
                    std::vector<std::string> vertexAttribsString;
                    boost::split(vertexAttribsString, tokens[1], boost::is_any_of("/"), boost::algorithm::token_compress_on);

                    processVertex(vertexAttribsString, vertexCoordinates, textureUV,
                                  normals, vertexCoordinatesArray, textureCoordinatesArray, indexesArray);

                    //processVertex(vertexAttribsString, vertexCoordinates, textureUV,
                    //              normals, vertexCoordinatesArray, textureCoordinatesArray, indexesArray);
                }

            }
            catch (const std::invalid_argument & e)
            {
                std::cerr << e.what() << '\n';
            }
            catch (const std::out_of_range & e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        //for (size_t i = 0; i < VERTICES_ARRAY_SIZE; ++i)
        //    std::cout << vertexCoordinatesArray[i] << std::endl;
    }

	void OBJParser::processVertex(const std::vector<std::string> & vertexStrings,
			                      const std::vector<std::tuple<float,float,float>> & vertexVector,
			                      const std::vector<std::pair<float,float>> & textureVector,
			                      const std::vector<std::tuple<float,float,float>> & normalsVector,
			                      float * vertexArray,
			                      float * textureArray,
			                      uint  * indexesArray)
    {
        (void)normalsVector;
        (void)indexesArray;
        (void)textureArray;
        (void)textureVector;
        static uint offset;

        uint vertexIndex = static_cast<uint>(std::stoi(vertexStrings[0])) - 1;
        auto [x, y, z] = vertexVector[vertexIndex];

        vertexArray[offset * 3] = x;
        vertexArray[offset * 3 + 1] = y;
        vertexArray[offset * 3 + 2] = z;

//        uint textureIndex = static_cast<uint>(std::stoi(vertexStrings[1])) - 1;
//        auto [u, v] = textureVector[textureIndex];
//
//        textureArray[offset * 2] = u;
//        textureArray[offset * 2 + 1] = 1 - v;

        ++offset;
    }

} // GE