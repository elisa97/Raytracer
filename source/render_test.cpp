#include "../framework/renderer.hpp"
#include "../framework/scene.hpp"

int main(int argc, char* argv[]){
    Scene new_scene;
    new_scene.background = {0.2f, 0.4f, 2.0f};
    Renderer new_renderer{600, 400, "output.ppm"};
    //Material new_material = new Material{};
    std::shared_ptr<Material> mat_ptr(new Material{"test mat", {0.8f, 0.2f, 0.2f}, {0.9f, 0.9f, 0.9f}, {0.2f, 0.4f, 0.5f}, 10.0f, 0.0f, 0.0f});
    std::shared_ptr<Material> matz_ptr(new Material{"test matz", {0.3f, 0.1f, 0.7f}, {0.8f, 0.5f, 0.8f}, {0.2f, 0.4f, 0.5f}, 10.0f, 1.0f, 0.0f});
    std::shared_ptr<Sphere> sphere_ptr(new Sphere{{0.0f, -0.5f, -4.0f}, 0.5f, "test_sphere", mat_ptr});
    std::shared_ptr<Box> box_ptr(new Box{{-1.5f,-4.4f,-5.0f}, {-1.0f,-0.3f,-3.0f}, "test_box", matz_ptr});
    //std::shared_ptr<Sphere> sphere_ptr2(new Sphere{{-1, 0, -2}, 0.2f, "test_sphere", mat_ptr});
    Light light_1{"new light", 50.0f, {0.5f, 0.5f, 0.5f}, {5.0f, 3.0f, 0.0f}};
    new_scene.objects.push_back(sphere_ptr);
    new_scene.objects.push_back(box_ptr);
    //new_scene.objects.push_back(sphere_ptr2);
    new_scene.ambient = {{0.5f}, {0.4f}, {0.7f}};
    new_scene.lights.push_back(light_1);

    new_renderer.render(new_scene, {});

    return 0;
}