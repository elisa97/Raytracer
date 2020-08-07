#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "hitpoint.hpp"

class Sphere : public Shape {
  public:
    Sphere();
    ~Sphere();
    Sphere(glm::vec3 const& m, float r);
    Sphere(glm::vec3 const& m, float r, std::string const& n, Color const& c);
    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream & os) const override;
    HitPoint intersect(Ray const& r) const; 
  private:
    glm::vec3 mid_;
    float rad_;
};


#endif