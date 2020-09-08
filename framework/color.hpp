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

// header, extern
#include <glm/glm.hpp>

// header, system
#include <iostream>

struct Color
{
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  void color_check()
  {
    glm::clamp(r, 0.0f, 1.0f);
    glm::clamp(g, 0.0f, 1.0f);
    glm::clamp(b, 0.0f, 1.0f);
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    this->color_check();
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    this->color_check();
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
    g *= a;
    b *= a;
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

  friend Color operator*(Color const& a, float b)
  {
    auto tmp(a);
    tmp *= b;
    return tmp;
  }

};

#endif