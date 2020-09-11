// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <omp.h>
#include <chrono>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render(Scene const& current_scene, unsigned int ref_step, 
                      unsigned int aa_step)
{
  std::chrono::steady_clock::time_point beg = std::chrono::steady_clock::now();
  if (aa_step > 4){
    aa_step = 4;
  }
  aa_step = pow(2, aa_step);
  
  Camera cam = current_scene.camera;
  std::size_t const checker_pattern_size = 20;
  float aspect_ratio = height_ / (float)width_;
  //bool to toggle the checkerboard pattern
  std::cout << "\nRendering to " << filename_  << "\n";
  bool debug = false;
  if (debug){
    std::cout << "threads = " << omp_get_max_threads() << "\n"
              << "aa      = " << aa_step << "\n"
              << "depth   = " << ref_step << "\n"
              << "objects = " << current_scene.objects.size() << "\n"
              << "lights  = " << current_scene.lights.size() << "\n\n";
  }
  bool chck = false;
    for (unsigned y = 0; y < height_; ++y) {
      #pragma omp parallel for
      for (unsigned x = 0; x < width_; ++x) {
      //setting up the rays
      float fov_dst = (width_ / 2.0f) / std::tan(cam.fov_x * M_PI / 360.0f);
      float aa = (1.0f / aa_step);
      Pixel p(x,y);
      for (float fl_x = x; fl_x < x+1; fl_x += aa) {
        for (float fl_y = y; fl_y < y+1; fl_y += aa) {
          //fov
          glm::vec3 ray_vec {fl_x - (width_ / 2.0f), 
                             fl_y - (height_ / 2.0f), -fov_dst};
          Ray current_eye_ray {cam.position, glm::normalize(ray_vec)};
          current_eye_ray = transform_ray(current_eye_ray, cam.camera_transformation);
          //intersection test
          HitPoint test_hp = closest_hit(current_scene, current_eye_ray);

          if (test_hp.cut) {
            p.color += calc_color(test_hp, current_scene, ref_step, ref_step)
                               * (aa / aa_step);
            //normals(p.color, test_hp);
          } 
          else if (chck) {
            if (((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
                p.color = Color{0.0f, 1.0f, float(x)/height_};
            } else {
              p.color = Color{1.0f, 0.0f, float(y)/width_};
            }
          }
          else {
            p.color += current_scene.background * (aa / aa_step);
          }
        }
      }
      write(p);
    }
    progress(y);
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  int t = std::chrono::duration_cast<std::chrono::seconds>(end - beg).count();
  std::cout << "\t\t\t\t [" << t << "s]\n";

  ppm_.save(filename_);
}

void Renderer::progress(float const y) const {

  float bar = 26.0f; 
  float prog = bar / height_;
  int pos = prog * y;
  std::cout << "[";
  for (int i = 0; i < bar-1; ++i) {
    if (i < pos) std::cout << "=";
    else std::cout << " "; 
  }
  std::cout << "] " << pos * 4 << "%  \r";
  if (y == height_) std::cout << std::endl;
  else std::cout.flush();
}

//includes transformation bc of intersect
HitPoint Renderer::closest_hit(Scene const& current_scene, 
                               Ray const& current_eye_ray) const {
  HitPoint test_hp {};
  test_hp.cdist = MAXFLOAT;
  HitPoint tmp_hp{};
  for (auto const& i : current_scene.objects) {
    tmp_hp = i.second->intersect(current_eye_ray);
    if (tmp_hp.cut) {
      if ((tmp_hp.cdist < test_hp.cdist) && (tmp_hp.cdist >= 0)) {
        test_hp = tmp_hp;
      }
    }
  }
  return test_hp;
}

Color Renderer::calc_color(HitPoint const& hp, Scene const& current_scene,
                           unsigned int reflection_steps, 
                           unsigned int refraction_steps) const{
  Color final {};
  Color phong = calc_phong(hp, current_scene);
  Color reflection = calc_reflection(hp, current_scene, reflection_steps,
                                     refraction_steps);
  Color refraction = calc_refraction(hp, current_scene, reflection_steps,
                                     refraction_steps);
  Color with_reflection = (phong * (1 - hp.material->glossy) 
                          + reflection * hp.material->glossy);
  final = with_reflection * hp.material->opacity 
                          + refraction * (1.0f - hp.material->opacity);
  //final = (phong * (1 - hp.material->glossy) 
  //        + reflection * hp.material->glossy);
  tone_mapping(final);
  return final;
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

Color Renderer::calc_phong(HitPoint const& hitpoint, Scene const& scene) const
{
  std::vector<Color> final_colors{};
  Color final_diffuse, final_specular, final;

  //ambient
  Color final_ambient = scene.background * hitpoint.material->ka;
 
  for (auto lights : scene.lights){

    glm::vec3 l = glm::normalize(lights.location - hitpoint.hit);
    Ray hit_light = {hitpoint.hit + 0.1f * hitpoint.normal, l};

    //shadows
    HitPoint shadow = closest_hit(scene, hit_light);
    if (!shadow.cut || shadow.material->opacity < 0.001f){

      //diffuse
      Color kd = hitpoint.material->kd;
      glm::vec3 n = glm::normalize(hitpoint.normal);
      float diff_prod = glm::clamp(glm::dot(n, l), 0.0f, 1.0f);
      final_diffuse = kd * diff_prod * lights.intensity;

      //specular
      float m = hitpoint.material->m;
      Color ks = hitpoint.material->ks;
      glm::vec3 r = glm::normalize(glm::reflect(l, n));
      // glm::vec3 r = glm::normalize(i - 2 * glm::dot(i, n) * n);
      glm::vec3 v = glm::normalize(hitpoint.direction);
      float spec_prod = glm::clamp(glm::dot(r, v), 0.0f, 1.0f);
      final_specular = ks * std::pow(spec_prod, m) * lights.intensity;

      final_colors.push_back(final_diffuse + final_specular);
    }
  }
  final = final_ambient;

  for (auto color : final_colors) {
    final += color;
  }
  return final;

}


Color Renderer::calc_reflection(HitPoint const& hitpoint, Scene const& scene,
                                unsigned int recursive_boundary1,
                                unsigned int recursive_boundary2) const 
{
  glm::vec3 incoming_direction = glm::normalize(hitpoint.direction);
  glm::vec3 normal = glm::normalize(hitpoint.normal);
  // glm::vec3 reflect_ray_dir = incoming_direction - 2 * 
  //           (glm::dot(normal, incoming_direction)) * normal;
  glm::vec3 reflect_ray_dir = glm::reflect(incoming_direction, normal);
  Ray reflect_ray {hitpoint.hit + 0.1f * normal,
                   glm::normalize(reflect_ray_dir)};
  HitPoint next_hit = closest_hit(scene, reflect_ray);

  if (recursive_boundary1 > 0 && next_hit.cut) {
    if (next_hit.material->glossy == 0.0f) {
      return calc_color(next_hit, scene, 0, recursive_boundary2) * 0.8f;
    }
    return calc_color(next_hit, scene, recursive_boundary1-1,
                      recursive_boundary2) * 0.8f;
  }
  return scene.background;
}

Color Renderer::calc_refraction(HitPoint const& hitpoint, Scene const& scene,
                                unsigned int recursive_boundary1, 
                                unsigned int recursive_boundary2) const 
{
  glm::vec3 incoming_direction = glm::normalize(hitpoint.direction);
  glm::vec3 normal = glm::normalize(hitpoint.normal);
  float opacity = hitpoint.material->opacity;
  float eta = 1.0f / hitpoint.material->eta;
  glm::vec3 refract_dir = glm::refract(incoming_direction, normal, eta);
  Ray refract_ray {hitpoint.hit - 0.001f * normal,
                  glm::normalize(refract_dir)};
  HitPoint next_hit = closest_hit(scene, refract_ray);

  if (recursive_boundary2 > 0 && next_hit.cut) {
    if(hitpoint.material->m == next_hit.material->m) {
      //refract_dir = glm::refract(glm::normalize(next_hit.direction), normal, -eta);
      Ray refract_ray_new {next_hit.hit + 0.001f * next_hit.normal, incoming_direction};
      HitPoint hp_out = closest_hit(scene, refract_ray_new);
      if (hp_out.cut) {
        if (hp_out.material->opacity == 1) {
          return calc_color(hp_out, scene, recursive_boundary1, 0);
        }
      return calc_color(hp_out, scene, recursive_boundary1,
                        recursive_boundary2-1);
      }
    }
    else {
      if (next_hit.material->opacity == 1) {
          return calc_color(next_hit, scene, recursive_boundary1, 0);
        }
      return calc_color(next_hit, scene, recursive_boundary1,
                        recursive_boundary2-1);
    }
    
  }
  return scene.background;
}

void Renderer::tone_mapping(Color &color) const 
{
  color.r = color.r / (color.r + 1);
  color.g = color.g / (color.g + 1);
  color.b = color.b / (color.b + 1);
}

void Renderer::normals(Color &color, HitPoint const& hp) const 
{
  color.r = hp.normal.x;
  color.g = hp.normal.y;
  color.b = hp.normal.z;
}