#include "ray.hpp"

Ray transformRay(Ray const& ray, glm::mat4 const& mat) {
        glm::vec4 p{ray.origin_,1};
        glm::vec4 v{ray.direction_,0};
        p = mat*p;
        v = mat*v;
        return {glm::vec3{p.x, p.y, p.z}, glm::vec3{v.x, v.y, v.z}};
}