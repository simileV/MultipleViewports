#ifndef CORE_H
#define CORE_H

#include <windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/norm.hpp>
#include <gtx/transform.hpp>
#include <gtx/string_cast.hpp>
#include <gtx/compatibility.hpp>
#include <gtx/color_space.hpp>
#include <gtx/component_wise.hpp>
#include <gtx/vector_angle.hpp>
#include <gtx/matrix_decompose.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include <chrono>
#include <random>
#include <algorithm>
#include <assert.h>
#include <string>
#include <vector>
#include <cstddef>
#include <map>
#include <fstream>
#include <filesystem>

typedef struct
{
	int width, height;
	int monitorX, monitorY;

	GLFWwindow *GLFWwin;
	glm::ivec2 winPosGlobal;

} Abj;

#endif