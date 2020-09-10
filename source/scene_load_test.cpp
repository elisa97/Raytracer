#include "../framework/scene.hpp"
#include "../framework/renderer.hpp"

int main(int argc, char* argv[]){
  std::string path = "../source/scene_test.sdf";
  std::string path2 = "../source/scene_test_2.sdf";
  std::string path3 = "../source/scene_test_3.sdf";

  Scene test = importScene(path, false);
  // Scene test2 = importScene(path2, false);
  // Scene test3 = importScene(path3, false);

  return 0;
}
