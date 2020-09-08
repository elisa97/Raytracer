#include "../framework/renderer.hpp"
#include "../framework/scene.hpp"
#include "glm/gtx/string_cast.hpp"

int main(int argc, char* argv[]){
    Scene new_scene;
    new_scene.background = {0.0f, 0.0f, 0.0f};
    Renderer new_renderer{1000, 800, "output2.ppm"};
    //Materials
    std::shared_ptr<Material> mat1_ptr (new Material{"red", {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, 10.0f, 0.3f, 0.7f});
    std::shared_ptr<Material> mat2_ptr (new Material{"green", {0.0, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f}, 3.0f, 0.0f, 0.2f});
    std::shared_ptr<Material> mat3_ptr (new Material{"blue", {0.0, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, 100.0f, 0.9f, 0.7f});
    std::shared_ptr<Material> mat4_ptr (new Material{"orange", {0.5, 0.2f, 0.0f}, {0.4f, 0.2f, 0.0f}, {0.4f, 0.2f, 0.0f}, 20.0f, 0.5f, 0.5f});
    std::shared_ptr<Material> mat5_ptr (new Material{"white", {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.7f, 0.7f, 0.7f}, 3.0f, 0.3f, 0.7f});
    //Spheres
    std::shared_ptr<Sphere> debug_sphere (new Sphere{{3.0f, 0.0f, -3.0f}, 1.0f, "debug sphere", mat1_ptr});
    //Boxes
    std::shared_ptr<Box> box1_ptr (new Box{{-2.0f, -0.9f, -1.5f}, {-0.5f,-0.3f,-1.0f}, "box1", mat4_ptr});

    //Triangle
    std::shared_ptr<Triangle> tirangle (new Triangle{{0.5f, 0.5f, -0.5f}, {0.3f, 0.3f, -0.3f}, {1.0f, 1.0f, -1.0f}, "tri", mat3_ptr});

    //Lights
    Light light1{"light1", 2.0f, {0.8f, 0.8f, 0.8f}, {3.0f, 1.0f, -3.0f}};
    Light light2{"light2", 5.0f, {0.7f, 0.7f, 0.7f}, {0.6f, 3.0f, 0.0f}};

    //Camera
    new_scene.camera.fov_x = 90;

    //Rotation
    std::stringstream info;
    
    // std::cout << glm::to_string(box1_ptr->world_transformation_) << std::endl;
    box1_ptr->print(info);
    std::vector<glm::vec3> position = box1_ptr->mv_mid();
    box1_ptr->print(info);
    box1_ptr->transformation({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 30.0f, {1.0f, 0.0f, 0.0f});
    box1_ptr->print(info);
    box1_ptr->mv_back(position);
    box1_ptr->print(info);
    //box1_ptr->transformation({1.0f, 1.0f, 1.0f}, {0.0f, 5.0f, 0.0f}, 0.0f, {0, 0, 0});
    // box1_ptr->print(box_info);
    // std::cout << box_info.rdbuf();
    // std::cout << glm::to_string(box1_ptr->world_transformation_) << std::endl;
    // std::cout << glm::to_string(debug_sphere->world_transformation_) << std::endl;
    position = debug_sphere->mv_mid();
    debug_sphere->print(info);
    debug_sphere->transformation({1.0f, 3.0f, 1.0f}, {-3.0f, 1.0f, -10.0f}, 60.0f, {0.0f, 1.0f, 0.0f});
    debug_sphere->mv_back(position);
    debug_sphere->print(info);

    // std::cout << glm::to_string(debug_sphere->world_transformation_) << std::endl;

    tirangle->print(info);
    std::cout << info.rdbuf();
    //new_scene.objects.push_back(box1_ptr);
    //new_scene.objects.push_back(debug_sphere);
    new_scene.objects.push_back(tirangle);
    new_scene.ambient = {"ambi", 0.2f, {0.6f, 0.7f, 0.9f}, {}};
    new_scene.lights.push_back(light1);
    new_scene.lights.push_back(light2);

    new_renderer.render(new_scene, 5, 2);

    return 0;
}