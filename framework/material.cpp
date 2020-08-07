#include "Material.hpp"

std::ostream& Material::print(std::ostream& os)
{
os  << "name: " << name_ << "\n" 
    << "ka: " << ka_ << "\n"
    << "kd: " << kd_ << "\n"
    << "ks: " << ks_ << "\n"
    << "spectular: " << m_ << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, Material& material)
{
    return material.print(os);
}

bool operator ==(Material const& lhs, Material const& rhs)
{
  if(lhs.name_.compare(rhs.name_) == 0)
  {
    return true;
  }
  else{return false;}
}