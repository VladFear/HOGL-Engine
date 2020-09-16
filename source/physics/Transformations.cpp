#include <physics/Transformations.h>

// TODO: Test this CAREFULLY
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
