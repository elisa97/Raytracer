#include "camera.hpp"

#include <cmath>

#define BUW_MATH_PI 3.14159265359

Camera::Camera(float fov = 50.0, glm::vec3 const& pos = glm::vec3(0.0, 0.0, 0.0)) :
    fov_h(fov), position(pos) {
        float half_angle_h = fov_h * BUW_MATH_PI / (2.0 * 180);
        dist_to_image_plane = 0.5 / std::tan(half_angle_h);
    }

void Camera::generate_eye_ray(float x, float y, Ray& out_ray) const {
    auto ray_direction = glm::vec3(x, y, -dist_to_image_plain) - position;

    out_ray.origin = position;
    out_ray.direction = ray_direction;
}