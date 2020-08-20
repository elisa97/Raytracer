#include "../framework/scene.hpp"
#include "../framework/renderer.hpp"

int main(int argc, char* argv[]){
  std::string path = "../source/scene_test.sdf";
  std::string path2 = "../source/scene_test_2.sdf";
  Scene test = importScene(path, false);
  Renderer new_renderer{600, 400, "output.ppm"};
  new_renderer.render(test, {});
  Scene test2 = importScene(path2, false);

  return 0;
}
