#include "scene.hpp"


Scene importScene(std::string const& sdf_file)
    {
    std::fstream file;
    std::string line;

    file.open(sdf_file, std::ios::in | std::fstream::out | std::fstream::app);
    if (!file){ std::cerr << "Could not open the file!" << std::endl;}

    }
    file.close();
}
