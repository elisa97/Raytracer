#ifndef CAMERA_HPP
#define CAMERA_HPP
#define GLM_FORCE_RADIANS

//header, project
#include "ray.hpp"

// header, external
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	void translate(glm::vec3 const& v) {
		camera_transformation = glm::translate(camera_transformation, v);
		camera_transformation_inv = glm::inverse(camera_transformation);
	}
	void rotate(float angle, glm::vec3 const& v) {
		if(angle != 0.0f) {
			camera_transformation = glm::rotate(camera_transformation, glm::radians(angle), v);
			camera_transformation_inv = glm::inverse(camera_transformation);
		}
	}
	void scale(glm::vec3 const& v) {
		camera_transformation = glm::scale(camera_transformation, v);
		camera_transformation_inv = glm::inverse(camera_transformation); 
	}
};

#endif