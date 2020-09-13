#include "../framework/scene.hpp"
#include "../framework/renderer.hpp"

int main(int argc, char* argv[]){
  std::string path = "../source/scene_1.sdf";
  std::string path2 = "../source/scene_2.sdf";
  std::string path3 = "../source/scene_3.sdf";
  //to not alter the original file and prevent data loss
  std::string anim = "../build/animation.tmp";

  bool verbose = false;
  // Scene test = importScene(path, false);
  // Scene test2 = importScene(path2, false);
  // Scene test3 = importScene(path3, false);
  Scene animation_scene = importScene(anim, verbose);

  return 0;
}
