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

      HitPoint test_hp = closest_hit(current_scene, current_eye_ray);
      

      Pixel p(x,y);
      if (test_hp.cut) {
        //p.color = calc_ambient(test_hp.material, current_scene);
        //p.color.r = test_hp.normal.x;
        //p.color.g = test_hp.normal.y;
        //p.color.b = test_hp.normal.z;
        p.color = calc_diffuse(test_hp, current_scene);
        //tone_mapping(p.color);
        //p.color = calc_reflection(test_hp, current_scene, 40);
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

HitPoint Renderer::closest_hit(Scene const& current_scene, Ray const& current_eye_ray) const {
  HitPoint test_hp {};
  test_hp.cdist = MAXFLOAT;
  HitPoint tmp_hp{};
  for (auto const& i : current_scene.objects) {
    tmp_hp = i->intersect(current_eye_ray);
    if (tmp_hp.cut) {
      if ((tmp_hp.cdist < test_hp.cdist) && (tmp_hp.cdist >= 0)) {
        test_hp = tmp_hp;
      }
    }
  }
  return test_hp;
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

Color Renderer::calc_diffuse(HitPoint const& hitpoint, Scene const& scene) const {
  Color final {0.0f, 0.0f, 0.0f};
  std::vector<Color> light_color;
  for (auto light: scene.lights){
    HitPoint no_light;
    glm::vec3 new_hitpoint;
    glm::vec3 new_normal;
    glm::vec3 light_hit = glm::normalize(light.location - hitpoint.hit);
    bool invisible_light = false;

    //check, if some other objects between light and object
    for (auto shape: scene.objects){
      no_light = shape->intersect(Ray{hitpoint.hit + 3.0f * hitpoint.normal, light_hit});
      if (no_light.cut){
        if(no_light.material->opacity < 0.001){
          invisible_light = true;
          break;    //if there is an object between light and object
        }
      }
    }

    //if there isn't a light blocking object
    if (!no_light.cut){
      float o = glm::dot(light_hit, glm::normalize(hitpoint.normal));
      Color i_p = light.color  * light.brightness;
      Color k_d = hitpoint.material->kd;
      light_color.push_back(k_d * i_p * o); 
    }
  }

  for (auto color: light_color){
    final += color;
  }

  final.color_check();
  return final;
}

Color Renderer::calc_reflection(HitPoint const& hitpoint, Scene const& scene, unsigned int recursive_boundary) const {
  Color final {0.0f, 0.0f, 0.0f};
  glm::vec3 incoming_direction = glm::normalize(hitpoint.origin);
  glm::vec3 normal = glm::normalize(hitpoint.normal);
  glm::vec3 reflect_ray_dir = incoming_direction - 2 * (glm::dot(normal, incoming_direction)) * normal;
  Ray reflect_ray {hitpoint.hit + 1.0f, glm::normalize(reflect_ray_dir)};
  HitPoint next_hit = closest_hit(scene, reflect_ray);

  if (!next_hit.cut){
    return scene.background;
  }
  else {
    if (recursive_boundary > 0 && next_hit.cut) {
      Color reflect_color = calc_ambient(hitpoint.material, scene);
      tone_mapping(reflect_color);
      //Color reflect_color = calc_color(next_hit, scene, recursive_boundary -1) * 0.8f;
      return reflect_color;
    }
    else
    {
      tone_mapping(final);
      return final;
    }
  }
}

void Renderer::tone_mapping(Color &color) const {
  color.r = color.r / (color.r + 1);
  color.g = color.g / (color.g + 1);
  color.b = color.b / (color.b + 1);
}


