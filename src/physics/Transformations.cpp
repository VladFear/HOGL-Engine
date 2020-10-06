#include <physics/Transformations.h>

std::ostream& operator<<(std::ostream& os, const glm::mat4& matrix)
{
	std::string matrix_str = glm::to_string(matrix);
	std::vector<std::string> vec;

	// Split by vectors
	boost::split(vec, matrix_str, boost::is_any_of("()"), boost::token_compress_on);
	// Remove empty string
	vec.pop_back();
	// Remove extra strings
	auto end = boost::range::remove_if(vec, [](const std::string& str) { return str == ", "; });

	vec.erase(end, vec.end());

	for (const auto & element : vec)
		os << element << '\n';

	return os;
}

glm::mat4 createTransformationMatrix(const glm::vec3 & translation,
                                     const glm::vec3 & rotation,
                                     const glm::vec3 & scaling)
{
	glm::mat4 trans_matrix = glm::mat4(1.0f);

	trans_matrix = glm::translate(trans_matrix, translation);

	trans_matrix = glm::rotate(trans_matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	trans_matrix = glm::rotate(trans_matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	trans_matrix = glm::rotate(trans_matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	trans_matrix = glm::scale(trans_matrix, scaling);

	return trans_matrix;
}

glm::mat4 createProjectionMatrix()
{
	// TODO: Remove hardcode of following variables.
	float FIELD_OF_VIEW = 70.f;
	float NEAR_PLANE = 0.1f;
	float FAR_PLANE = 1000.f;

	int width = 1366;
	int height = 768;

	glm::mat4 projection_matrix = glm::perspective(glm::radians(FIELD_OF_VIEW),
	                                               static_cast<float>(width) / static_cast<float>(height),
	                                               NEAR_PLANE,
	                                               FAR_PLANE);

	return projection_matrix;
}

glm::mat4 createViewMatrix(const glm::vec3 & position,
                           const glm::vec3 & direction,
                           const glm::vec3 & up)
{
	return glm::lookAt(position, direction, up);
}
