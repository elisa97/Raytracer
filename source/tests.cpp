#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "../framework/box.hpp"
#include "../framework/sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE("area and vol for sphere", "[Sphere]") {
  Sphere t1;
  float area = t1.area();
  float vol = t1.volume();
  REQUIRE(area == Approx(1256.637f));
  REQUIRE(vol == Approx(4188.791f));
  Sphere t2({2, 2, 2}, 2.0f);
  area = t2.area();
  vol = t2.volume();
  REQUIRE(area == Approx(50.266f));
  REQUIRE(vol == Approx(33.51f));
  Sphere t3({2, 2, 2}, -2.0f);
  area = t3.area();
  vol = t3.volume();
  REQUIRE(area == Approx(50.266f));
  REQUIRE(vol == Approx(33.51f));
  Sphere t4({2, 2, 2}, 0.0f);
  area = t4.area();
  vol = t4.volume();
  REQUIRE(area == Approx(0.0f));
  REQUIRE(vol == Approx(0.0f));
  Sphere t5({2, 2, 2}, M_PI);
  area = t5.area();
  vol = t5.volume();
  REQUIRE(area == Approx(124.025f));
  REQUIRE(vol == Approx(129.879f));
}

TEST_CASE("area and vol for box", "[Box]") {
  Box b1;
  float area = b1.area();
  float vol = b1.volume();
  REQUIRE(area == Approx(0.0f));
  REQUIRE(vol == Approx(0.0f));
  Box b2{{3.0f, 2.0f, 1.0f}, {3.0f, 2.0f, 1.0f}};
  area = b2.area();
  vol = b2.volume();
  REQUIRE(area == Approx(0.0f));
  REQUIRE(vol == Approx(0.0f));
  Box b3{{3.0f, 2.0f, 1.0f}, {4.0f, 2.0f, -1.0f}};
  area = b3.area();
  vol = b3.volume();
  REQUIRE(area == Approx(4.0f));
  REQUIRE(vol == Approx(0.0f));
  Box b4{{3.0f, -2.0f, 1.0f}, {4.0f, 2.0f, 0.0f}};
  area = b4.area();
  vol = b4.volume();
  REQUIRE(area == Approx(18.0f));
  REQUIRE(vol == Approx(4.0f));
  Box b5{{3.7f, 2.8f, 1.1f}, {4.5f, 2.1f, 0.7f}};
  area = b5.area();
  vol = b5.volume();
  REQUIRE(area == Approx(2.32f));
  REQUIRE(vol == Approx(0.224f));
}

TEST_CASE("outputstream test", "[os]") {
  std::shared_ptr<Material> mat1(new Material{});
  Box b1 {};
  Box b2 {{12,5,10}, {10,1,5}};
  Box b3 {{0,-2,8}, {-3,-7,3}, "test_1", mat1};
  Sphere s1 {};
  Sphere s2{{1.5f,5.3f,2.7f},4.51f};
  Sphere s3{{3,1,5}, 21.0f, "test_2", mat1};

  std::cout << "1\n";
  std::cout << b1;
  std::cout << "2\n";
  std::cout << b2;
  std::cout << b3;
  std::cout << s1;
  std::cout << s2;
  std::cout << s3;

  std::ostringstream str1;
  str1 << b1;
  std::string cstr1 = 
  "Box default\nMaterial default\nPoints (0, 0, 0)\n\t\t (0, 0, 0)\n";
  REQUIRE(str1.str() == cstr1);
  std::ostringstream str2;
  str2 << b2;
  std::string cstr2 = 
  "Box default\nMaterial default\nPoints (10, 1, 5)\n\t\t (12, 5, 10)\n";
  REQUIRE(str2.str() == cstr2);
  std::ostringstream str3;
  str3 << b3;
  std::string cstr3 = 
  "Box test_1\nMaterial default\nPoints (-3, -7, 3)\n\t\t (0, -2, 8)\n";
  REQUIRE(str3.str() == cstr3);
  std::ostringstream str4;
  str4 << s1;
  std::string cstr4 = 
  "Sphere default\nMaterial default\nMiddle (0, 0, 0) \n Radian 10\n";
  REQUIRE(str4.str() == cstr4);
  std::ostringstream str5;
  str5 << s2;
  std::string cstr5 = 
  "Sphere default\nMaterial default\nMiddle (1.5, 5.3, 2.7) \n Radian 4.51\n";
  REQUIRE(str5.str() == cstr5);
  std::ostringstream str6;
  str6 << s3;
  std::string cstr6 = 
  "Sphere test_2\nMaterial default\nMiddle (3, 1, 5) \n Radian 21\n";
  REQUIRE(str6.str() == cstr6);
}

TEST_CASE("intersect_ray_sphere", "[intersect_s]") {
  //Ray
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  //ray direction has to be normalized
  //you can use:
  //v = glm::normalize(some_vector);
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

  //Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};

  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
  ray_origin, ray_direction, sphere_center,
  sphere_radius * sphere_radius, distance); 
  REQUIRE(distance == Approx(4.0f)); 
  
  //same test as above but more compact
  Ray r1 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f}};
  Sphere c1 {{0.0f, 0.0f, 5.0f}, 1.0f};
  auto hp = c1.intersect(r1);
  REQUIRE(hp.cdist == Approx(4.0f));
  REQUIRE(hp.cut == true);

  //if radian is equal to zero
  Ray r2 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f}};
  Sphere c2 {{0.0f, 0.0f, 1.0f}, 0.0f};
  hp = c2.intersect(r2);
  REQUIRE(hp.cdist== Approx(1.0f)); 
  REQUIRE(hp.cut== true);

  //not intersecting
  Ray r3 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f}};
  Sphere c3 {{0.0f, 0.1f, 1.0f}, 0.0f};
  hp = c3.intersect(r3);
  REQUIRE(hp.cdist == Approx(-1.0f));
  REQUIRE(hp.cut == false);

  //negative radian
  Ray r4 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f}};
  Sphere c4 {{0.0f, 0.0f, 5.0f}, -1.0f};
  hp = c4.intersect(r4);
  REQUIRE(hp.cdist == Approx(4.0f));
  REQUIRE(hp.cut == true);

  //ray in opposite direction
  Ray r5 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, -1.0f}};
  Sphere c5 {{0.0f, 0.0f, 5.0f}, 1.0f};
  hp = c5.intersect(r5);
  REQUIRE(hp.cdist == Approx(-1.0f));
  REQUIRE(hp.cut == false);

  //ray starts somwhere inside the circle
  Ray r6 {{0.0f, 2.0f, 1.0f},{0.0f, 3.0f, -2.0f}};
  Sphere c6 {{5.0f, 2.0f, 2.0f}, 10.0f};
  hp = c6.intersect(r6);
  REQUIRE(hp.cdist == Approx(8.0655f));
  REQUIRE(hp.cut == true);

  //ray goes trough the exact middle of the sphere
  Ray r7 {{5.0f, 2.0f, 7.0f},{2.0f, 1.5f, 1.0f}};
  Sphere c7 {{19.0f, 12.5f, 14.0f}, 3.0f};
  hp = c7.intersect(r7);
  REQUIRE(hp.cdist == Approx(15.848f));
  REQUIRE(hp.cut == true);

  //ray touches the sphere
  Ray r8 {{-4.0f, 2.0f, 9.0f},{0.0f, 0.3f, 1.7f}};
  Sphere c8 {{-6.29999f, 3.89f, 19.71f}, 2.3f};
  hp = c8.intersect(r8);
  REQUIRE(hp.cdist == Approx(10.87f));
  REQUIRE(hp.cut == true);
  REQUIRE(hp.name == "default");

  //ray almost touches the sphere bc 6.3f != 6.3
  Ray r9 {{-4.0f, 2.0f, 9.0f},{0.0f, 0.3f, 1.7f}};
  Sphere c9 {{-6.3f, 3.89f, 19.71f}, 2.3f};
  hp = c9.intersect(r9);
  REQUIRE(hp.cdist == Approx(-1));
  REQUIRE(hp.cut == false);
}

TEST_CASE("intersect_ray_box", "[intersect_b]") {
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
  Ray r1{ray_origin, ray_direction};
  Box b1 {};
  Box b2 {{3.0f, 2.0f, 3.0f}, {2.0f, -3.0f, 1.0f}, "Box 2", {}};
  auto hp = b1.intersect(r1);
  REQUIRE(hp.cdist == Approx(-0.0001f)); //?
  REQUIRE(hp.cut == true);
}

TEST_CASE("con- and destructor", "[deconst]") {
  std::shared_ptr<Material> mat1 (new Material{});
  glm::vec3 position{0.0f, 0.0f, 0.0f};

  Sphere* s1 = new Sphere{position, 1.2f, "sphere0", mat1};
  Sphere* s2 = new Sphere{position, 1.2f, "sphere1", mat1};

  s1->print(std::cout);
  s2->print(std::cout);

  delete s1;
  delete s2;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}