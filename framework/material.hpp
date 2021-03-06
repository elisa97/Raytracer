#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// header, project
#include "color.hpp"

// header, extern
#include <glm/glm.hpp>

// header, system
#include <iostream>
#include <string>

struct  Material
{
	std::string name = "default";
	Color       ka {0.0f,0.0f,0.0f};
	Color       kd {0.0f,0.0f,0.0f};
	Color       ks {0.0f,0.0f,0.0f};
	float       m = 1.0f;
	float       opacity = 0.0f;
	float       glossy = 0.0f;
	float				eta = 1.0f;

	std::ostream& print(std::ostream& os);

	void material_check()
	{
		ka.color_check();
		kd.color_check();
		ks.color_check();
		if (m < 0) m = 0;
		glm::clamp(opacity, 0.0f, 1.0f);
		glm::clamp(glossy, 0.0f, 1.0f);
		glm::clamp(eta, 0.0f, 3.0f);
	}   
};

std::ostream& operator<<(std::ostream& os, Material& material);

bool operator ==(Material const& lhs, Material const& rhs);

#endif