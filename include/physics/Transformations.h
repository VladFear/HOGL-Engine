#pragma once

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm.hpp>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

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
                                     const glm::vec3 & scaling);
