#include <maths/Transformations.h>

namespace GE
{

	std::ostream& operator<<(std::ostream& os, const mat4 & matrix)
	{
		std::string matrixStr = glm::to_string(matrix);
		std::vector<std::string> vec;

		// Split by vectors
		boost::split(vec, matrixStr, boost::is_any_of("()"), boost::token_compress_on);
		// Remove empty string
		vec.pop_back();
		// Remove extra strings
		auto end = boost::range::remove_if(vec, [](const std::string & str) { return str == ", "; });

		vec.erase(end, vec.end());

		for (const auto & element : vec)
			os << element << '\n';

		return os;
	}

	mat4 createTransformationMatrix(const vec3 & translation,
	                                const vec3 & rotation,
	                                const vec3 & scaling)
	{
		mat4 transformMatrix = mat4(1.0f);

		transformMatrix = glm::translate(transformMatrix, translation);

		transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), vec3(1, 0, 0));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), vec3(0, 1, 0));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), vec3(0, 0, 1));

		transformMatrix = glm::scale(transformMatrix, scaling);

		return transformMatrix;
	}

	mat4 createProjectionMatrix()
	{
		float NEAR_PLANE = std::get<float>(RenderProperties::getProperty("NEAR_PLANE"));
		float FAR_PLANE  = std::get<float>(RenderProperties::getProperty("FAR_PLANE"));
		float FOV        = std::get<float>(RenderProperties::getProperty("FIELD_OF_VIEW"));

		// TODO: Remove hardcode of following variables.
		int width = 1366;
		int height = 768;

		mat4 projectionMatrix = glm::perspective(
			glm::radians(FOV),
			static_cast<float>(width) / static_cast<float>(height),
			NEAR_PLANE,
			FAR_PLANE);

		return projectionMatrix;
	}

	mat4 createViewMatrix(const vec3 & position,
	                      const vec3 & direction,
	                      const vec3 & up)
	{
		return glm::lookAt(position, direction, up);
	}

} // GE
