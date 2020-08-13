#ifndef SHAPE_HPP
#define SHAPE_HPP

// header, system
#include <memory>

// header, project
#include "color.hpp"
#include "hitpoint.hpp"


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
};
std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif