#include "../framework/scene.hpp"
#include "../framework/renderer.hpp"

int main(int argc, char* argv[]){
  std::string path = "../source/scene_test.sdf";
  Scene test = importScene(path);
  Renderer new_renderer{600, 400, "output.ppm"};
  new_renderer.render(test);

  return 0;
}
