// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render(Scene const& current_scene)
{
  std::size_t const checker_pattern_size = 20;
  float aspect_ratio = height_ / (float)width_;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

      //setting up the rays
      glm::vec3 ray_vec = {{x / float(width_) -0.5f}, {aspect_ratio * (y / float(height_) -0.5f)}, {-1.0f}};
      glm::vec3 ray_norm = glm::normalize(ray_vec);
      Ray current_eye_ray {{}, ray_norm};

      //tried to iterate trough the vector, checking which object is the closest to the camera
      HitPoint test_hp{};
      test_hp.cdist = MAXFLOAT;
      HitPoint tmp_hp{};
      for (auto const& i : current_scene.objects) {
        tmp_hp = i->intersect(current_eye_ray);

        if (tmp_hp.cut) {
          if (((test_hp.cdist < 0) && (tmp_hp.cdist >= 0)) || ((tmp_hp.cdist < test_hp.cdist) && (test_hp.cdist >= 0))) {
            test_hp = tmp_hp;
          }
        }
      }

      Pixel p(x,y);
      if (test_hp.cut) {
        //p.color = Color{test_hp.material->ka.r, test_hp.material->ka.g, test_hp.material->ka.b};
        //p.color = Color{1.0f, 1.0f, 1.0f/test_hp.cdist};
        p.color = calc_ambient(test_hp.material, current_scene);
        tone_mapping(p.color);
      } else if (((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

Color Renderer::calc_ambient(std::shared_ptr<Material> const& material, Scene const& scene) const {
  Color ambient{scene.ambient};
  ambient.r = material->ka.r * ambient.r;
  ambient.g = material->ka.g * ambient.g;
  ambient.b = material->ka.b * ambient.b;
  return ambient;
}

void Renderer::tone_mapping(Color &color) const {
  color.r = color.r / (color.r + 1);
  color.g = color.g / (color.g + 1);
  color.b = color.b / (color.b + 1);
}
//HitPoint Renderer::generate_eye_ray(Scene const& scene, Ray const& ray) const {}

