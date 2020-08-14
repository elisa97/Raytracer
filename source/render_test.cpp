#include "../framework/renderer.hpp"
#include "../framework/scene.hpp"

int main(int argc, char* argv[]){
    Scene new_scene;
    Renderer new_renderer{600, 400, "output.ppm"};
    //Material new_material = new Material{};
    std::shared_ptr<Material> mat_ptr(new Material{});
    std::shared_ptr<Sphere> sphere_ptr(new Sphere{{0, 0, -2}, 0.5f, "test_sphere", mat_ptr});
    new_scene.objects.push_back(sphere_ptr);

    new_renderer.render(new_scene);

    return 0;
}