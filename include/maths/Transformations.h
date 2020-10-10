#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm.hpp>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace GE
{

	using vec3 = glm::vec3;
	using mat4 = glm::mat4;

	std::ostream& operator<<(std::ostream & os, const mat4 & matrix);

	mat4 createTransformationMatrix(const vec3 & translation,
	                                const vec3 & rotation,
	                                const vec3 & scaling);

	mat4 createProjectionMatrix();

	mat4 createViewMatrix(const vec3 & position,
	                      const vec3 & direction,
	                      const vec3 & up);

} // GE
