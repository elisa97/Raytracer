#ifndef LIGHT_HPP
#define LIGHT_HPP

// header, project
#include "color.hpp"

// header, external
#include <glm/vec3.hpp>

struct Light
{
	std::string name = "default";
	float       brightness = 0.5f;
	Color       color {0.5f, 0.5f, 0.5f};
	glm::vec3   location {0.0f, 0.0f, 0.0f};
	Color       intensity = {color.r * brightness, 
															color.g * brightness, color.b * brightness};
};

#endif