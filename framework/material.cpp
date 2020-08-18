#include "material.hpp"

std::ostream& Material::print(std::ostream& os)
{
os  << "name: " << name << "\n" 
    << "ka: " << ka << "\n"
    << "kd: " << kd << "\n"
    << "ks: " << ks << "\n"
    << "spectular: " << m << "\n"
    << "opacity: " << opacity << "\n"
    << "glossy: " << glossy << "\n";
  return os;
}

std::ostream& operator<<(std::ostream& os, Material& material)
{
    return material.print(os);
}

bool operator ==(Material const& lhs, Material const& rhs)
{
  if(lhs.name.compare(rhs.name) == 0)
  {
    return true;
  }
  else{return false;}
}