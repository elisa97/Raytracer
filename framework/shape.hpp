#ifndef SHAPE_HPP
#define SHAPE_HPP
#define GLM_FORCE_RADIANS

// header, project
#include "color.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"

// header, external
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

// header, system
#include <memory>
#include <vector>
#include <cmath>

class Shape {
  public:
    Shape();
    Shape(std::shared_ptr<Material> material,std::string const& name);
    virtual ~Shape();
    virtual float area() const = 0;
    virtual float volume() const = 0; 
    virtual HitPoint intersect(Ray const& ray) const = 0;
    virtual std::ostream& print(std::ostream& os) const;
    virtual void transformation(glm::vec3 const& scale, 
                                glm::vec3 const& translation, 
                                float angle, glm::vec3 const& axis);
    virtual std::vector<glm::vec3> mv_mid();
    virtual void mv_back(std::vector<glm::vec3> const& v);


  protected:
    std::shared_ptr<Material> material_;
    std::string name_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
};

Ray transform_ray(Ray const& ray, glm::mat4 const& mat);
void rev_trans(HitPoint & hitpoint, glm::mat4 const& world, glm::mat4 const& world_inv);
std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif