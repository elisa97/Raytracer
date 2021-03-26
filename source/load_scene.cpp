#include "../framework/scene.hpp"
#include "../framework/renderer.hpp"

int main(int argc, char* argv[]) {

  std::string file = "../build/animation.tmp";
  bool verbose = false;

  if (argc == 2) {
    std::string arg(argv[1]);
    if (arg.compare("1") == 0) {
      file = "../source/scene_1.sdf";
    }
    else if (arg.compare("2") == 0) {
      file = "../source/scene_2.sdf";
    }
    else if (arg.compare("3") == 0) {
      file = "../source/scene_3.sdf";
    }
    else {
      file = "../source/" + arg;
    }
  }
  
  Scene animation_scene = importScene(file, verbose);

  return 0;
}
