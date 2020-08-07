#include "scene.hpp"


Scene importScene(std::string const& sdf_file)
    {
    std::fstream file;
    std::string line;

    file.open(sdf_file, std::ios::in | std::fstream::out | std::fstream::app);
    if (!file){ std::cerr << "Could not open the file!" << std::endl;}

    while(std::getline(file, line))
    {
        std::stringstream lstream(line);
        std::string keyword;
        lstream >> keyword; 

        if(keyword == "define")
        {
            lstream >> keyword;
            if(keyword == "material")
            {
                Material mat;

                lstream >> mat.name_;

                lstream >> mat.ka_.r;
                lstream >> mat.ka_.g;
                lstream >> mat.ka_.b;

                lstream >> mat.kd_.r;
                lstream >> mat.kd_.g;
                lstream >> mat.kd_.b;

                lstream >> mat.ks_.r;
                lstream >> mat.ks_.g;
                lstream >> mat.ks_.b;
                
                lstream >> mat.m_;
                //Hier wird jedes durch ein whitespace getrenntes string/float etc. (wird selbstständig interpretiert)
                //in den jeweiligen Variablen gespeichert 

                matCont.push_back(std::make_shared<Material>(mat));
            }

            if(keyword == "sphere")
            {
                glm::vec3 center;
                float radius;

                lstream >> center.x;
                lstream >> center.y;
                lstream >> center.z;

                lstream >> radius;

                Sphere sphere{center, radius};
                sphCont.push_back(sphere);       
            }

            if(keyword == "box")
            {
                glm::vec3 min;
                glm::vec3 max;

                lstream >> min.x;
                lstream >> min.y;
                lstream >> min.z;

                lstream >> max.x;
                lstream >> max.y;
                lstream >> max.z;

                Box box{min, max};
                boxCont.push_back(box);
            }
        }
    }
    file.close();
}
