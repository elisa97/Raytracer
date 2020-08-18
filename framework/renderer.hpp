// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

// header, external

#include <glm/glm.hpp>

// header, system
#include <string>

// header, project
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "material.hpp"

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  void render(Scene const& current_scene, Camera const& cam);
  void write(Pixel const& p);

  Color calc_color(HitPoint const& hitpoint, Scene const& current_scene) const;
  Color calc_ambient(std::shared_ptr<Material> const& material, Scene const& scene) const;
  Color calc_diffuse(HitPoint const& hitpoint, Scene const& scene) const;
  Color calc_reflection(HitPoint const& hitpoint, Scene const& scene, unsigned int recursive_boundary) const; 
  HitPoint closest_hit(Scene const& current_scene, Ray const& current_eye_ray) const;
  void tone_mapping(Color & color) const;

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};



#endif // #ifndef BUW_RENDERER_HPP
