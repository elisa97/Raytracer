#include "../framework/renderer.hpp"
#include "../framework/scene.hpp"

int main(int argc, char* argv[]){
    Scene new_scene;
    Renderer new_renderer(600, 400, "output.ppm");
    
    new_renderer.render(new_scene);

    return 0;
}