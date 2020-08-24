#include "../framework/renderer.hpp"
#include "../framework/scene.hpp"

int main(int argc, char* argv[]){
    Scene new_scene;
    new_scene.background = {0.0f, 0.0f, 0.0f};
    Renderer new_renderer{1000, 800, "output.ppm"};
    //Material new_material = new Material{};
    std::shared_ptr<Material> mat1_ptr(new Material{"red", {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, 10.0f, 0.3f, 0.7f});
    std::shared_ptr<Material> mat2_ptr(new Material{"green", {0.0, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f}, 3.0f, 0.0f, 0.0f});
    std::shared_ptr<Material> mat3_ptr(new Material{"blue", {0.0, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, 10.0f, 0.3f, 0.9f});
    std::shared_ptr<Material> mat4_ptr(new Material{"orange", {0.5, 0.2f, 0.0f}, {0.4f, 0.2f, 0.0f}, {0.4f, 0.2f, 0.0f}, 20.0f, 0.5f, 0.5f});
    std::shared_ptr<Material> mat5_ptr(new Material{"white", {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, 10.0f, 0.3f, 0.7f});

    std::shared_ptr<Sphere> sphere_ptr(new Sphere{{0.0f, -0.3f, -5.0f}, 0.5f, "test_sphere", mat1_ptr});
    std::shared_ptr<Box> box_ptr(new Box{{-1.5f,-4.4f,-5.0f}, {-0.9f,-0.2f,-3.0f}, "test_box", mat3_ptr});
    std::shared_ptr<Box> box_ptr3(new Box{{-1.5f,-4.4f,-15.0f}, {-1.0f,-0.3f,-2.0f}, "test_box", mat1_ptr});
    std::shared_ptr<Sphere> sphere_ptr2(new Sphere{{-0.7, -0.8f, -2.5f}, 0.3f, "test_sphere", mat3_ptr});
    std::shared_ptr<Box> box_ptr2(new Box{{-1.5f,-1.0f,-1.0f}, {1.0f,-3.0f,-10.0f}, "test_box", mat4_ptr});
    std::shared_ptr<Box> box_ptr4(new Box{{1.5f,-4.4f,-15.0f}, {1.0f,-0.3f,-2.0f}, "test_box", mat1_ptr});
    Light light_1{"new light", 3.0f, {0.8f, 0.8f, 0.8f}, {3.0f, 1.0f, -3.0f}};
    Light light_2{"new light1", 30.0f, {0.7f, 0.7f, 0.7f}, {0.6f, 3.0f, 0.0f}};
    Light placeholder_light{"just a placeholder", 0.0f, {0.0f, 0.0f, 0.0f}, {}};
    
    new_scene.objects.push_back(sphere_ptr);
    new_scene.objects.push_back(sphere_ptr2);
    new_scene.objects.push_back(box_ptr);
    new_scene.objects.push_back(box_ptr3);
    new_scene.objects.push_back(box_ptr2);
    new_scene.objects.push_back(box_ptr4);
    new_scene.ambient = {"ambi", 0.9f, {0.9f, 0.9f, 0.9f}, {}};
    //new_scene.lights.push_back(light_1);
    //new_scene.lights.push_back(light_2);
   
    

    new_renderer.render(new_scene, {});

    return 0;
}