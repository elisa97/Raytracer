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

  void render(Scene const& current_scene);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }
  //HitPoint Renderer::generate_eye_ray(Scene const& scene, Ray const& ray) const;

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};



#endif // #ifndef BUW_RENDERER_HPP
