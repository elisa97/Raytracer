// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

// header, system
#include <iostream>

struct Color
{

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  void color_check(){
    if (r > 1){
      r = 1;
    }
    else if (r < 0){
      r =0;
    }
    if (g > 1){
      g = 1;
    }
    else if (g < 0){
      g = 0;
    }
    if (b > 1){
      b = 1;
    }
    else if (b < 0){
      b = 0;
    }
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*=(Color const& other)
  {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    this->color_check();
    return *this;
  }

  Color& operator*=(float a)
  {
    r *= a;
    g *= g;
    b *= b;
    this->color_check();
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

friend Color operator*(Color const& a, Color const& b)
{
  auto tmp(a);
  tmp *= b;
  return tmp;
}

friend Color operator*(Color const& a, float const& b)
{
  auto tmp(a);
  tmp *= b;
  return tmp;
}

  float r;
  float g;
  float b;
};

#endif //#define BUW_COLOR_HPP
