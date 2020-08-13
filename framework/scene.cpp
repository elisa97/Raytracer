#include "scene.hpp"

Scene importScene(std::string const& sdf_file) {
   
    std::ifstream in_file(sdf_file, std::ios::in);
    std::string line_buffer;
    int32_t line_count = 0;
    Scene new_scene;

    std::string identifier;
    std::string class_name;

    std::vector<std::string> materials;
    std::vector<std::string> shape_mats;


    while( std::getline(in_file, line_buffer) ) {
        std::cout << ++line_count << ":" << line_buffer << std::endl;

        //construct stringstream using line_buffer string
        std::istringstream in_sstream(line_buffer);

        in_sstream >> identifier;

        std::cout << "Identifiert content: " << identifier << std::endl;

        //check for shapes, materials, lights
        if("define" == identifier) {
            in_sstream >> class_name;

            if("shape" == class_name ) {
                in_sstream >> class_name;
                if("box" == class_name){
                    std::string box_name;
                    glm::vec3 box_v1, box_v2;
                    std::string box_mat_name;

                    in_sstream >> box_name;
                    in_sstream >> box_v1.x >> box_v1.y >> box_v1.z;
                    in_sstream >> box_v2.x >> box_v2.y >> box_v2.z;
                    in_sstream >> box_mat_name;

                    //using a vector to store and later check materials
                    shape_mats.push_back(box_mat_name);

                    //Debug 
                    std::cout << "Shape: Box: " << box_name << std::endl;
                    std::cout << "Vec1: (" << box_v1.x << ", " << box_v1.y << ", " << box_v1.z << ")" << std::endl;
                    std::cout << "Vec2: (" << box_v2.x << ", " << box_v2.y << ", " << box_v2.z << ")" << std::endl;
                    std::cout << "Box Material Name: " << box_mat_name;
                }

                else if("sphere" == class_name){
                    std::string sphere_name;
                    glm::vec3 sphere_m;
                    float sphere_r;
                    std::string sphere_mat_name;

                    in_sstream >> sphere_name;
                    in_sstream >> sphere_m.x >> sphere_m.y >> sphere_m.z;
                    in_sstream >> sphere_r;

                    //same as with box
                    shape_mats.push_back(sphere_mat_name);

                    //Debug
                    std::cout << "Shape: Sphere: " << sphere_name << std::endl;
                    std::cout << "Center m: (" << sphere_m.x << ", " << sphere_m.y << ", " << sphere_m.z << ")" << std::endl;
                    std::cout << "Radius r: " << sphere_r << std::endl;
                    std::cout << "Sphere Material: " << sphere_mat_name << std::endl;
                }
                else{
                    std::cout << "Error! No valid shape." << std::endl;
                }
            
            } else if("material" == class_name){
                std::string material_name;
                glm::vec3 ka, kd, ks;
                float m;

                in_sstream >> material_name;
                in_sstream >> ka.r >> ka.g >> ka.b;
                in_sstream >> kd.r >> kd.g >> kd.b;
                in_sstream >> ks.r >> ks.g >> ks.b;

                //vector to staore materials
                materials.push_back(material_name);
                
                //Debug
                std::cout << "Object: Material: " <<  material_name << std::endl;
                std::cout << ka.r << " " << ka.g << " " << ka.b << std::endl;
                std::cout << kd.r << " " << kd.g << " " << kd.b << std::endl;
                std::cout << ks.r << " " << ks.g << " " << ks.b << std::endl;
                std::cout << m << std::endl;

            } else if("light" == class_name) {
                std::string light_name;
                glm::vec3 light_pos, light_color;
                float light_brightness;

                in_sstream >> light_name;
                in_sstream >> light_pos.x >> light_pos.y >> light_pos.z;
                in_sstream >> light_color.r >> light_color.g >> light_color.b;
                in_sstream >> light_brightness;

                //Debug
                std::cout << "Object: Light: " << light_name << std::endl;
                std::cout << "Position: (" << light_pos.x << ", " << light_pos.y << ", " << light_pos.z << ")" << std::endl;
                std::cout << "Color: (" << light_color.r << " " << light_color.g << " " << light_color.b << ")" << std::endl;
                std::cout << "Brightness: " << light_brightness << std::endl;
            } 
            else {
                std::cout << "Line was not valid!" << std::endl;
            }
        }
    }

    in_file.close();

    //checking if all the materials are availible
    //generating extra array with each material of the shapes only once present, checking that with the materials array to make sure that all
    //each shape has a valid material, otherwise print a error message.
    std::vector<std::string> tmp_mat;
    if (shape_mats.size() > 0) {
        tmp_mat.push_back(shape_mats[0]);
    }
    for (int i = 1; i < shape_mats.size(); ++i) {
        for (int j = 0; j < tmp_mat.size(); ++j) {
            
        }
    }
}