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
		// TODO: Remove hardcode of following variables.
		float FIELD_OF_VIEW = 70.f;
		float NEAR_PLANE = 0.1f;
		float FAR_PLANE = 1000.f;

		int width = 1366;
		int height = 768;

		mat4 projectionMatrix = glm::perspective(
			glm::radians(FIELD_OF_VIEW),
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
