#ifndef CAMERA_HPP
#define CAMERA_HPP

//header, project
#include "ray.hpp"

// header, external
#include <glm/vec3.hpp>

// header, system
#include <string>
#include <fstream>
#include <sstream>

struct Camera {

	std::string name = "default";
	float 			fov_x = 60.0f;  // between 0 and 180
	glm::vec3 	position {0.0f, 0.0f, 0.0f};
	glm::vec3 	direction {0.0f, 0.0f, -1.0f};
	glm::vec3 	up {0.0f, 1.0f, 0.0f};
	glm::mat4 	camera_transformation { 1.0f, 0.0f, 0.0f, 0.0f, 
																			0.0f, 1.0f, 0.0f, 0.0f,
																			0.0f, 0.0f, 1.0f, 0.0f, 
																			0.0f, 0.0f, 0.0f, 1.0f };
	glm::mat4 	camera_transformation_inv = 
							glm::inverse(camera_transformation);
};

#endif