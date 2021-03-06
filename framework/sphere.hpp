#ifndef SPHERE_HPP
#define SPHERE_HPP

// header, project
#include "shape.hpp"

class Sphere : public Shape {
  public:
    Sphere();
    ~Sphere();
    Sphere(glm::vec3 const& m, float r);
    Sphere(glm::vec3 const& m, float r, std::string const& name,
           std::shared_ptr<Material> material);
    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream & os) const override;
    HitPoint intersect(Ray const& r) const override;

  private:
    glm::vec3 mid_;
    float     rad_;
};

#endif