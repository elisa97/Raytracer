#ifndef SHAPE_HPP
#define SHAPE_HPP

// header, extzernal
#include <glm/glm.hpp>

// header, system
#include <memory>

// header, project
#include "color.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"


class Shape {
  public:
    Shape();
    Shape(std::shared_ptr<Material> material,std::string const& name);
    virtual ~Shape();

    virtual float area() const = 0;
    virtual float volume() const = 0; 
    virtual HitPoint intersect(Ray const& ray) const = 0;
    virtual std::ostream& print(std::ostream& os) const;
    std::string name_;
    
  protected:
    std::shared_ptr<Material> material_;
    glm::mat4 world_transformation_, world_transformation_inv_;
};
std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif