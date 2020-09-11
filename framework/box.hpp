#ifndef BOX_HPP
#define BOX_HPP

// header, project
#include "shape.hpp"

// header, system
#include <algorithm>

class Box : public Shape {
  public:
    Box();
    Box(glm::vec3 const& lhs, glm::vec3 const& rhs);
    Box(glm::vec3 const& lhs, glm::vec3 const& rhs, 
        std::string const& name, std::shared_ptr<Material> material);
    float area() const override;
    float volume() const override;
    void  min_max();
    void  intersect_plane(HitPoint& hitpoint, Ray const& ray, int dim,
                          bool side, float plane_value) const;
    HitPoint intersect(Ray const& ray) const override;
    std::ostream& print(std::ostream & os) const override;

  private:
    glm::vec3 min_;
    glm::vec3 max_;

};

#endif