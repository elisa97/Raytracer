#include "../framework/renderer.hpp"
#include "../framework/scene.hpp"

int main(int argc, char* argv[]){
    Scene new_scene;
    Renderer new_renderer{600, 400, "output.ppm"};
    Material new_material{};
    std::shared_ptr<Material> mat_ptr = new_material;
    Sphere new_sphere{{-2, 0, 0}, 0.5, mat_ptr};
    std::shared_ptr<Sphere> sphere_ptr = new_sphere ;
    new_scene.objects.push_back(sphere_ptr);

    new_renderer.render(new_scene);

    return 0;
}