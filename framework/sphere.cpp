#include "sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <cmath>

Sphere::Sphere() {
  mid_ = {0.0f, 0.0f, 0.0f};
  rad_ = 10.0f;
  name_ = "Jeff";
  color_ = {0.0f, 0.0f, 0.0f};
}

Sphere::~Sphere() {
  std::cout << "Dstr/Sphere " << name_ << "\n";
}

Sphere::Sphere(glm::vec3 const& m , float r)  {
  mid_ = m;
  rad_ = abs(r);
  name_ = "Jeff";
  color_ = {0.0f, 0.0f, 0.0f};
}

Sphere::Sphere(glm::vec3 const& m , float r, std::string const& n, Color const& c)  {
  std::cout << "Cnst/Sphere " << name_ << "\n";
  mid_ = m;
  rad_ = abs(r);
  name_ = n;
  color_ = c;
}

float Sphere::area() const {
  return (4.0f * M_PI * pow(rad_, 2.0f));
}

float Sphere::volume() const {
  return (4.0f / 3.0f * M_PI * pow(rad_, 3.0f));
}

std::ostream& Sphere::print(std::ostream & os) const {
   return os << "Sphere " << name_ << "\nRGB [" 
   << color_.r << "|" << color_.g << "|" << color_.b 
   << "]\nMiddle: (" << mid_.x << "|" << mid_.y << "|" << mid_.z 
   << ") Radian: " << rad_ << "\n\n";
}

HitPoint Sphere::intersect(Ray const& r) const {

  float d = 0.0f;
  glm::vec3 n = glm::normalize(r.direction);
  bool res = glm::intersectRaySphere(r.origin, n, mid_, rad_ * rad_, d);

  if (res) {
    glm::vec3 ct = r.origin + (d * n);
    return{true, d, name_, color_, {ct, n}};
  }
  
  return{};
}