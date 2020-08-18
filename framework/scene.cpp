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

    while(std::getline(in_file, line_buffer)) {

        std::cout << ++line_count << ":" << line_buffer << std::endl;

        std::istringstream in_sstream(line_buffer);
        in_sstream >> identifier;
        if ("define" == identifier) {
            in_sstream >> class_name;
            if ("material" == class_name) {
                std::string material_name;
                glm::vec3 ka, kd, ks;
                float m;

                in_sstream >> material_name >> ka.r >> ka.g >> ka.b>> kd.r >> 
                        kd.g >> kd.b >>ks.r >> ks.g >> ks.b >> m;

                std::shared_ptr<Material> mt_ptr (new Material{material_name, 
                    {ka.r, ka.g, ka.b}, {kd.r, kd.g, kd.b},{ks.r, ks.g, ks.g}, m});

                new_scene.materials.emplace(material_name, mt_ptr);
            }
        }
    line_count = 0;
    while(std::getline(in_file, line_buffer)) {
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

                    in_sstream >> box_name >> box_v1.x >> box_v1.y >> box_v1.z
                        >> box_v2.x >> box_v2.y >> box_v2.z >> box_mat_name;

                    //TODO check if the name was actually found
                    std::shared_ptr<Material> box_material = new_scene.materials.find(box_mat_name)->second;
                    std::shared_ptr<Box> sp_ptr (new Box{box_v1, box_v2, box_name, box_material});
                    new_scene.objects.push_back(sp_ptr);
                    
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

                    in_sstream >> sphere_name >> sphere_m.x >> sphere_m.y >> sphere_m.z
                        >> sphere_r >> sphere_mat_name;

                    //TODO check if the name was actually found
                    std::shared_ptr<Material> sphere_material = new_scene.materials.find(sphere_mat_name)->second;
                    std::shared_ptr<Sphere> sp_ptr (new Sphere{sphere_m, sphere_r, sphere_name, sphere_material});
                    new_scene.objects.push_back(sp_ptr);

                    //Debug
                    std::cout << "Shape: Sphere: " << sphere_name << std::endl;
                    std::cout << "Center m: (" << sphere_m.x << ", " << sphere_m.y << ", " << sphere_m.z << ")" << std::endl;
                    std::cout << "Radius r: " << sphere_r << std::endl;
                    std::cout << "Sphere Material: " << sphere_mat_name << std::endl;
                }
                else{
                    std::cout << "Error! No valid shape." << std::endl;
                }
            
            // } else if("material" == class_name){
            //     std::string material_name;
            //     glm::vec3 ka, kd, ks;
            //     float m;

            //     in_sstream >> material_name;
            //     in_sstream >> ka.r >> ka.g >> ka.b;
            //     in_sstream >> kd.r >> kd.g >> kd.b;
            //     in_sstream >> ks.r >> ks.g >> ks.b;

            //     //vector to staore materials
            //     materials.push_back(material_name);
                
            //     //Debug
            //     std::cout << "Object: Material: " <<  material_name << std::endl;
            //     std::cout << ka.r << " " << ka.g << " " << ka.b << std::endl;
            //     std::cout << kd.r << " " << kd.g << " " << kd.b << std::endl;
            //     std::cout << ks.r << " " << ks.g << " " << ks.b << std::endl;
            //     std::cout << m << std::endl;

            // } 
                } else if("light" == class_name) {
                std::string light_name;
                glm::vec3 light_pos, light_color;
                float light_brightness;

                in_sstream >> light_name;
                in_sstream >> light_pos.x >> light_pos.y >> light_pos.z;
                in_sstream >> light_color.r >> light_color.g >> light_color.b;
                in_sstream >> light_brightness;
                
                Light light{light_name, light_brightness, {light_color.r, light_color.g, light_color.b}, light_pos};
                new_scene.lights.push_back(light);
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

    }
    return new_scene;
}