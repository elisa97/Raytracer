#ifndef SCENE_HPP
#define SCENE_HPP

#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <glm/vec3.hpp>
#include "Material.hpp"
#include "Sphere.hpp"
#include "Box.hpp"

struct Scene
{
    std::vector<std::shared_ptr<Material>> matCont;
    std::vector<Sphere> sphCont;
    std::vector<Box> boxCont;

    void importScene(std::string const& path)
    {
    std::fstream file;
    std::string line;

    file.open(path, std::ios::in | std::fstream::out | std::fstream::app);
    if (!file){ std::cerr << "Could not open the file!" << std::endl;}

    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string keyword;
        ss >> keyword; 

        if(keyword == "define")
        {
            ss >> keyword;
            if(keyword == "material")
            {
                Material mat;

                ss >> mat.name_;

                ss >> mat.ka_.r;
                ss >> mat.ka_.g;
                ss >> mat.ka_.b;

                ss >> mat.kd_.r;
                ss >> mat.kd_.g;
                ss >> mat.kd_.b;

                ss >> mat.ks_.r;
                ss >> mat.ks_.g;
                ss >> mat.ks_.b;
                
                ss >> mat.m_;

                matCont.push_back(std::make_shared<Material>(mat));
            }

            if(keyword == "sphere")
            {
                glm::vec3 center;
                float radius;

                ss >> center.x;
                ss >> center.y;
                ss >> center.z;

                ss >> radius;

                Sphere sphere{center, radius};
                sphCont.push_back(sphere);       
            }

            if(keyword == "box")
            {
                glm::vec3 min;
                glm::vec3 max;

                ss >> min.x;
                ss >> min.y;
                ss >> min.z;

                ss >> max.x;
                ss >> max.y;
                ss >> max.z;

                Box box{min, max};
                boxCont.push_back(box);
            }
        }
    }
    file.close();
}
};

#endif