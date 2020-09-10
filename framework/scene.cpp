#include "scene.hpp"
#include "renderer.hpp"


glm::vec3 mv_mid(glm::vec3 & v1 ,glm::vec3 & v2)
{
	//check v1 & v2
	if (v1.x > v2.x) std::swap(v1.x, v2.x);
	if (v1.y > v2.y) std::swap(v1.y, v2.y);
	if (v1.z > v2.z) std::swap(v1.z, v2.z);
  glm::vec3 vec2mid = (v2 - v1) / 2.0f;
	glm::vec3 translate = v1 + vec2mid;
  v2 = vec2mid;
  v1 = -vec2mid;
	return translate;
}

Scene importScene(std::string const& sdf_file, bool verbose) 
{   
	std::ifstream in_file(sdf_file, std::ios::in);
	std::string line_buffer;
	int32_t line_count = 0;
	Scene new_scene;
	std::string identifier;
	std::string class_name;

  //first loop to get all of the materials

	while(std::getline(in_file, line_buffer)) {	

		std::istringstream in_sstream(line_buffer);
		in_sstream >> identifier;

		if ("define" == identifier){
			in_sstream >> class_name;

			if ("material" == class_name) {
				std::string material_name;
				glm::vec3 ka, kd, ks;
				float m, opacity, glossy, eta;

				in_sstream 
				>> material_name 
				>> ka.r >> ka.g >> ka.b
				>> kd.r >> kd.g >> kd.b 
				>> ks.r >> ks.g >> ks.b 
				>> m 
				>> opacity 
				>> glossy
				>> eta;

				std::shared_ptr<Material> mt_ptr (new Material{material_name,
																											{ka.r, ka.g, ka.b},
																											{kd.r, kd.g, kd.b},
																											{ks.r, ks.g, ks.g},
																											 m, opacity, glossy,
																											 eta});

				new_scene.materials.emplace(material_name, mt_ptr);

				if (verbose) {
					std::cout << "Material " <<  material_name << "\n"
										<< "ka (" 		 << ka.r 
										<< " " 				 << ka.g 
										<< " " 				 << ka.b 					 << ")\n"
										<< "kd ("			 << kd.r 
										<< " " 				 << kd.g 
										<< " " 				 << kd.b 					 << ")\n"
										<< "ks (" 		 << ks.r 
										<< " " 				 << ks.g 
										<< " " 				 << ks.b 					 << ")\n"
										<< " m " 			 << m 	
										<< " opacity " << opacity 
										<< " glossy "  << glossy
										<< " eta " 		 <<	eta			 			 << "\n";
				}
			}
		}
  }

  //resetting the ifstream back to the beginning

	line_count = 0;
	in_file.clear();
	in_file.seekg(0, std::ios::beg);

  //second loop to get all the other objects, linking the materials and shapes directly

  while (std::getline(in_file, line_buffer)) {
        
		//construct stringstream using line_buffer string
		std::istringstream in_sstream(line_buffer);
		in_sstream >> identifier;
        
		if (verbose) {
			std::cout << ++line_count 	<< ": " << line_buffer << "\n"
								<< "Identifier content: " << identifier  << "\n";
		}

		//check for shapes, lights
		if ("define" == identifier) {
				in_sstream >> class_name;

			if ("shape" == class_name ) {
				in_sstream >> class_name;

				if ("box" == class_name){

					std::string box_name;
					glm::vec3 box_v1, box_v2;
					std::string box_mat_name;

					in_sstream 
					>> box_name 
					>> box_v1.x >> box_v1.y >> box_v1.z
					>> box_v2.x >> box_v2.y >> box_v2.z 
					>> box_mat_name;

					std::shared_ptr<Material> box_material;
					box_material = new_scene.materials.find(box_mat_name)->second;

					//checking if the returned pointer is a nullpointer
					if (!box_material) {
						std::cout << "!ERROR: Material " << box_mat_name 
											<< " for box "				 << box_name
											<< " could not be found,"
											<< " reverting to the default material.\n";
						box_material = (std::shared_ptr<Material>(new Material{}));
					}
					glm::vec3 translate = mv_mid(box_v1, box_v2);

					std::shared_ptr<Box> sp_ptr (new Box{box_v1, box_v2, 
																							 box_name, box_material});
					sp_ptr->transformation({1.0f, 1.0f, 1.0f}, translate, 0.0f,{0.0f, 1.0f, 0.0f});
					new_scene.objects.push_back(sp_ptr);
                    
					if (verbose) {
							std::cout << "Box " 		 << box_name 		 << "\n"
												<< "Material " << box_mat_name << "\n"
												<< "Vec1 (" 	 << box_v1.x
												<< ", " 			 << box_v1.y
												<< ", " 			 << box_v1.z 		 << ")\n"
												<< "Vec2 ("		 << box_v2.x 
												<< ", " 			 << box_v2.y
												<< ", " 			 << box_v2.z 		 << ")\n";
					}
        }
				else if ("sphere" == class_name){

					std::string sphere_name;
					glm::vec3 sphere_m;
					float sphere_r;
					std::string sphere_mat_name;

					in_sstream 
					>> sphere_name 
					>> sphere_m.x >> sphere_m.y >> sphere_m.z
					>> sphere_r 
					>> sphere_mat_name;

					std::shared_ptr<Material> sphere_material;
					sphere_material = new_scene.materials.find(sphere_mat_name)->second;
					if (!sphere_material) {
							std::cout << "!ERROR: Material " << sphere_mat_name 
												<< " for sphere " 		 << sphere_name 
												<< " could not be found,"
												<< " reverting to the default material.\n";
							sphere_material = (std::shared_ptr<Material>(new Material{}));
					}
					std::shared_ptr<Sphere> sp_ptr (new Sphere{{0.0f, 0.0f, 0.0f}, sphere_r, 
																										 sphere_name, 
																										 sphere_material});
					sp_ptr->transformation({1.0f, 1.0f, 1.0f},sphere_m, 0.0f, {});	
					// std::shared_ptr<Sphere> sp_ptr (new Sphere{sphere_m, sphere_r, 
					// 																					 sphere_name, 
					// 																					 sphere_material});																		 
					new_scene.objects.push_back(sp_ptr);

					if (verbose) {
						std::cout << "Sphere " 	 << sphere_name 		<< "\n"
											<< "Material " << sphere_mat_name << "\n"
											<< "Center ("  << sphere_m.x 
											<< ", " 			 << sphere_m.y 
											<< ", " 			 << sphere_m.z 			<< ")\n"
											<< "Radius " 	 << sphere_r 				<< "\n";
					}
				}
				else {
					std::cout << "Error! " << class_name 
										<< " is not a valid shape." << "\n";
				}
            
      } 
			else if ("material" == class_name){

				if (verbose) {
					in_sstream >> class_name;
					auto ptr = new_scene.materials.find(class_name)->second;
					if (!ptr) {
						std::cout << "The material " << class_name 
											<< " could not be found or successfully initialized";
					}
					else {
						auto mat = ptr.get();
						std::cout << "Material " << mat->name 	 << "\n"
											<< "ka " 			 << mat->ka.r 
											<< " " 				 << mat->ka.g 
											<< " " 				 << mat->ka.b 	 << "\n"
											<< "kd " 			 << mat->kd.r 
											<< " " 				 << mat->kd.g 
											<< " "				 << mat->kd.b 	 << "\n"
											<< "ks "			 << mat->ks.r 
											<< " " 				 << mat->ks.g 
											<< " " 				 << mat->ks.b 	 << "\n"
											<< "m " 			 << mat->m 
											<< " opacity " << mat->opacity 
											<< " glossy "  << mat->glossy
											<< " eta "		 << mat->eta		 << "\n";
					}
        }

			} 
			else if ("ambient" == class_name) {

				std::string amb_name;
				Color amb_color;
				float amb_brightness;

				in_sstream 
				>> amb_name 
				>> amb_color.r >> amb_color.g >> amb_color.b 
				>> amb_brightness;

				new_scene.ambient = {amb_name, amb_brightness, amb_color, {}};
				new_scene.background = new_scene.ambient.intensity;
				std::cout << new_scene.background.r << " " << new_scene.background.r << " " << new_scene.background.g << " " << new_scene.background.b << "\n";

				if (verbose) {
					std::cout << "Ambient "		 << amb_name 			 << "\n"
										<< "Color (" 		 << amb_color.r 
										<< ", " 				 << amb_color.g 
										<< ", " 				 << amb_color.b 	 << ")\n"
					 					<< "Brightness " << amb_brightness << "\n";
				}
			}
			else if ("light" == class_name) {

				std::string light_name;
				glm::vec3 light_pos, light_color;
				float light_brightness;

				in_sstream 
				>> light_name 
				>> light_pos.x >> light_pos.y >> light_pos.z
				>> light_color.r >> light_color.g >> light_color.b 
				>> light_brightness;
                
				Light light{light_name, light_brightness, 
										{light_color.r, light_color.g, light_color.b},
										light_pos};
				new_scene.lights.push_back(light);
                
				if(verbose) {
					std::cout << "Light " 		 << light_name 			 << "\n"
					 					<< "Position ("  << light_pos.x 
										<< ", " 			   << light_pos.y 
										<< ", " 				 << light_pos.z 		 << ")\n"
					 					<< "Color ("		 << light_color.r 
										<< " " 					 << light_color.g 
										<< " " 					 << light_color.b 	 << ")\n"
					 					<< "Brightness " << light_brightness << "\n";
				}

			} 
			else if ("camera" == class_name) {

				std::string cam_name;
				float cam_fov;
				glm::vec3 cam_pos, cam_dir, cam_up;

				in_sstream 
				>> cam_name 
				>> cam_fov 
				>> cam_pos.x >> cam_pos.y >> cam_pos.z
				>> cam_dir.x >> cam_dir.y >> cam_dir.z 
				>> cam_up.x >> cam_up.y >> cam_up.z;

				new_scene.camera.name = cam_name;
				new_scene.camera.fov_x = cam_fov;
				new_scene.camera.position = cam_pos;
				new_scene.camera.direction = cam_dir;
				new_scene.camera.up = cam_up;

			}
    }
		if ("render" == identifier) {

			std::string cam_name, img_output;
			unsigned int img_x, img_y, ref_step, aa_step;

			in_sstream 
			>> cam_name 
			>> img_output 
			>> img_x >> img_y
			>> ref_step >> aa_step;

			Renderer renderer{img_x, img_y, img_output};
			renderer.render(new_scene, ref_step, aa_step);
		}
  }

	in_file.close();

	return new_scene;
}