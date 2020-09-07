#include "../framework/renderer.hpp"
#include "../framework/scene.hpp"

int main(int argc, char* argv[]){
    Scene new_scene;
    new_scene.background = {0.0f, 0.0f, 0.0f};
    Renderer new_renderer{800, 600, "output.ppm"};
    new_scene.camera.fov_x = 90;
    //Materials
    std::shared_ptr<Material> mat1_ptr (new Material{"red", {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, 10.0f, 0.3f, 0.7f});
    std::shared_ptr<Material> mat2_ptr (new Material{"green", {0.0, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f}, 3.0f, 0.0f, 0.2f});
    std::shared_ptr<Material> mat3_ptr (new Material{"blue", {0.0, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, 100.0f, 0.3f, 0.9f});
    std::shared_ptr<Material> mat4_ptr (new Material{"orange", {0.5, 0.2f, 0.0f}, {0.4f, 0.2f, 0.0f}, {0.4f, 0.2f, 0.0f}, 20.0f, 0.5f, 0.5f});
    std::shared_ptr<Material> mat5_ptr (new Material{"white", {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.7f, 0.7f, 0.7f}, 3.0f, 0.3f, 0.7f});
    //Spheres
    std::shared_ptr<Sphere> sphere1_ptr (new Sphere{{0.0f, -0.3f, -5.0f}, 0.5f, "sphere1", mat1_ptr});
    std::shared_ptr<Sphere> sphere2_ptr (new Sphere{{-0.7, -0.8f, -2.5f}, 0.3f, "sphere2", mat3_ptr});
    std::shared_ptr<Sphere> debug_sphere (new Sphere{{0.0f, 0.0f, -3.0f}, 1.0f, "debug sphere", mat5_ptr});
    //Boxes
    std::shared_ptr<Box> box1_ptr (new Box{{-1.5f,-4.4f,-5.0f}, {-0.9f,-0.2f,-3.0f}, "box1", mat3_ptr});
    std::shared_ptr<Box> box2_ptr (new Box{{-1.5f,-1.0f,-1.0f}, {1.0f,-3.0f,-10.0f}, "box3", mat4_ptr});
    std::shared_ptr<Box> box3_ptr (new Box{{-1.5f,-4.4f,-15.0f}, {-1.0f,-0.3f,-2.0f}, "box2", mat1_ptr});
    std::shared_ptr<Box> box4_ptr (new Box{{1.5f,-4.4f,-15.0f}, {1.0f,-0.3f,-2.0f}, "box4", mat2_ptr});
    //Lights
    Light light1{"light1", 3.0f, {0.8f, 0.8f, 0.8f}, {3.0f, 1.0f, -3.0f}};
    Light light2{"light2", 2.0f, {0.7f, 0.7f, 0.7f}, {0.6f, 3.0f, 0.0f}};
    Light placeholder_light{"just a placeholder", 0.0f, {0.0f, 0.0f, 0.0f}, {}};

    //Rotation
    //box1_ptr->transformation({2.0f, 2.0f, 2.0f}, {}, 60.0f, {1.0f, 1.0f, 0.0f});
    sphere1_ptr->transformation({0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, 0.0f, {});
    
    new_scene.objects.push_back(sphere1_ptr);
    new_scene.objects.push_back(sphere2_ptr);
    new_scene.objects.push_back(box1_ptr);
    new_scene.objects.push_back(box2_ptr);
    new_scene.objects.push_back(box3_ptr);
    new_scene.objects.push_back(box4_ptr);
    //new_scene.objects.push_back(debug_sphere);
    new_scene.ambient = {"ambi", 0.2f, {0.9f, 0.9f, 0.9f}, {}};
    new_scene.lights.push_back(light1);
    new_scene.lights.push_back(light2);
   
    

    new_renderer.render(new_scene);

    return 0;
}