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

std::ostream& operator<<(std::ostream& os, const glm::mat4& matrix);

glm::mat4 createTransformationMatrix(const glm::vec3 & translation,
                                     const glm::vec3 & rotation,
                                     const glm::vec3 & scaling);
