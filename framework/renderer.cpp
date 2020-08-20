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

void Renderer::render(Scene const& current_scene, Camera const& cam)
{
  std::size_t const checker_pattern_size = 20;
  float aspect_ratio = height_ / (float)width_;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

      //setting up the rays
      //glm::vec3 ray_vec = {{x / float(width_) -0.5f}, {aspect_ratio * (y / float(height_) -0.5f)}, {-1.0f}};
      //glm::vec3 ray_norm = glm::normalize(ray_vec);
      //tried to implement fov, not quite ready yet
      float fov_dist = (width_ / 2.0f) / std::tan(cam.fov_x * M_PI / 360.0f);
      glm::vec3 dir{x - (width_ / 2.0f), y - (width_ / 2.0f), -fov_dist};
      Ray current_eye_ray {{}, glm::normalize(dir)};

      HitPoint test_hp = closest_hit(current_scene, current_eye_ray);
      

      Pixel p(x,y);
      if (test_hp.cut) {
        //p.color = calc_ambient(test_hp.material, current_scene);
        //p.color.r = test_hp.normal.x;
        //p.color.g = test_hp.normal.y;
        //p.color.b = test_hp.normal.z;
        p.color = calc_color(test_hp, current_scene, 2);

        //tone_mapping(p.color);
        //p.color = calc_reflection(test_hp, current_scene, 40);
      //} else if (((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        //p.color = Color{0.0f, 1.0f, float(x)/height_};
        
      } else {
        //p.color = Color{1.0f, 0.0f, float(y)/width_};
        p.color = current_scene.background;
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

Color Renderer::calc_color(HitPoint const& hitpoint, Scene const& current_scene, unsigned int reflection_steps) const{
  Color final{0.0f, 0.0f, 0.0f};
  Color ambient = calc_ambient(hitpoint, current_scene);
  Color diffuse = calc_diffuse(hitpoint, current_scene);
  Color specular = calc_specular(hitpoint, current_scene);
  Color phong = ambient + diffuse + specular;
  Color reflection = calc_reflection(hitpoint, current_scene, reflection_steps);
  //final = (phong * (1 - hitpoint.material->glossy) + reflection * hitpoint.material->glossy);
  final = ambient + reflection;
  //final = phong;
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



Color Renderer::calc_ambient(HitPoint const& hp, Scene const& scene) const {
  Color ambient{};
  // ambient.r = material->ka.r * ambient.r;
  // ambient.g = material->ka.g * ambient.g;
  // ambient.b = material->ka.b * ambient.b;
  for (auto light: scene.lights){
    glm::vec3 light_hit = glm::normalize(light.location - hp.hit);
    ambient = ambient + scene.ambient.intensity * hp.material->ka + light.intensity * hp.material->kd  * glm::dot(hp.normal, light_hit);
  }
  return ambient;
}

Color Renderer::calc_diffuse(HitPoint const& hitpoint, Scene const& scene) const {
  Color final {0.0f, 0.0f, 0.0f};
  std::vector<Color> light_color;
  for (auto light: scene.lights){
    bool invisible_light;
    HitPoint no_light;
    glm::vec3 light_hit = glm::normalize(hitpoint.hit - light.location);
    Ray ray_to_light {hitpoint.hit + 0.1f * hitpoint.normal, -light_hit};

    for (auto obj: scene.objects) {
      no_light = obj->intersect(ray_to_light);

      if(no_light.cut){
        invisible_light = true;
      }

      if(!invisible_light){
        glm::vec3 ref_light = light_hit - 2*(glm::dot(light_hit, hitpoint.normal)) * hitpoint.normal;
        float aux = std::pow(glm::dot(ref_light, glm::normalize(scene.camera.position - hitpoint.hit)), hitpoint.material->m);
        Color ip = light.color * light.brightness;
        Color ks = hitpoint.material->ks;
        light_color.push_back(ks * aux * ip);
      }
    }
  }

  for (auto color : light_color){
    final += color;
  }

  return final;
}

//     //check, if some other objects between light and object
//     for (auto shape: scene.objects){
//       no_light = shape->intersect(Ray{hitpoint.hit + 3.0f * hitpoint.normal, light_hit});
//       if (no_light.cut){
//         if(no_light.material->opacity < 0.001){
//           invisible_light = true;
//           break;    //if there is an object between light and object
//         }
//       }
//     }

//    // if there isn't a light blocking object
//     if (!no_light.cut){
//       float o = glm::dot(light_hit, glm::normalize(hitpoint.normal));
//       Color i_p = light.color  * light.brightness;
//       Color k_d = hitpoint.material->kd;
//       light_color.push_back(k_d * i_p * o); 
//     }
//   }

//   for (auto color: light_color){
//     final += color;
//   }

//   final.color_check();
//   return final;
// }

Color Renderer::calc_specular(HitPoint const& hitpoint, Scene const& scene) const {
  Color final {0.0f, 0.0f, 0.0f};
  std::vector<Color> calc_color;

  for (auto light : scene.lights){
    bool invisible_light = false;
    HitPoint no_light;
    glm::vec3 light_hit = glm::normalize(light.location - hitpoint.hit);

    for (auto shape : scene.objects){
      no_light = shape->intersect(Ray{hitpoint.hit + 0.01f, light_hit});
      if (no_light.cut){
        //std::cout << ":)";
        if (no_light.material->opacity > 0.1){
          invisible_light = true;
          break;
        }
      }
    }

    if (!invisible_light) {
      //std::cout << "buh";
      //glm::vec3 camera_hit = glm::normalize(camera_hit - hitpoint.hit);
      glm::vec3 r = light_hit - 2*(glm::dot(light_hit, hitpoint.normal)) * hitpoint.normal;
      //float p = abs(glm::dot(r, camera_hit));
      //float cos = pow(p, hitpoint.material->m);
      //float m_pi = (hitpoint.material->m+ 2.0f) / (2 * M_PI);
      float m_pi = std::pow(glm::dot(r, glm::normalize(scene.camera.position - hitpoint.hit)), hitpoint.material->m);
      Color i_p = light.color * light.brightness;
      Color k_s = hitpoint.material->ks;
      calc_color.push_back(k_s * m_pi *  i_p);
    } else {
    //std::cout << "hi";
  }
  } 
//     Ray ray_to_light {hitpoint.hit + 0.1f * hitpoint.normal, light_hit};
//     no_light = scene.objects[0]->intersect(ray_to_light);

//     if(no_light.cut){
//       invisible_light = true;
//     }
//     if(!invisible_light){
//       float m = hitpoint.material->m;
//       glm::vec3 r = 2.0f*glm::dot(hitpoint.normal,light_hit)*hitpoint.normal-light_hit;
//       glm::vec3 v = glm::normalize(scene.camera.position - hitpoint.hit);

//       float aux = glm::dot(r, v);

//       if(aux < 0){
//         aux = -aux;
//       }

//       float cos = pow(aux, m);
//       float m2 = (m+2)/(2*M_PI);
//       Color ip = light.color * light.brightness;
//       Color ks = hitpoint.material->ks;

//       calc_color.push_back(ip * ks * cos * m2);
//     }
//   }
  
  for (auto color : calc_color){
    final += color;
  }
  return final;
}

Color Renderer::calc_reflection(HitPoint const& hitpoint, Scene const& scene, unsigned int recursive_boundary) const {
  Color final {0.0f, 0.0f, 0.0f};
  glm::vec3 incoming_direction = glm::normalize(hitpoint.direction);
  glm::vec3 normal = glm::normalize(hitpoint.normal);
  glm::vec3 reflect_ray_dir = incoming_direction - 2 * (glm::dot(normal, incoming_direction)) * normal;
  Ray reflect_ray {hitpoint.hit + 1.0f, reflect_ray_dir};
  HitPoint next_hit = closest_hit(scene, reflect_ray);

  if (!next_hit.cut){
    return scene.background;
    //return hitpoint.material->ka;
  }
  else {
    if (recursive_boundary > 0 && next_hit.cut) {
      Color reflect_color = calc_color(next_hit, scene, recursive_boundary -1) * 0.8f;
      return reflect_color;
    }
    else
    {
      return {};
    }
  }
}

void Renderer::tone_mapping(Color &color) const {
  color.r = color.r / (color.r + 1);
  color.g = color.g / (color.g + 1);
  color.b = color.b / (color.b + 1);
  //color = (color + 1);
}


