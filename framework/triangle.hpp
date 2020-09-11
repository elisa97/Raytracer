#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

// header, project
#include "shape.hpp"

// header, system
#include <algorithm>

class Triangle : public Shape {
  public:
    Triangle();
    Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c);
    Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c,
             std::string const& name, std::shared_ptr<Material> material);
    float area() const override;
    float volume() const override;
    HitPoint intersect(Ray const& ray) const override;      // not working
    std::ostream& print(std::ostream & os) const override;

  private:
    glm::vec3 a_;
    glm::vec3 b_;
    glm::vec3 c_;

};

#endif