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
  Box b1;
  Box b2 {{12,5,10}, {10,1,5}};
  Box b3 {{0,-2,8}, {-3,-7,3}, "Guntram", mat1};
  Sphere s1;
  Sphere s2{{1.5f,5.3f,2.7f},4.51f};
  Sphere s3{{3,1,5}, 21.0f, "Kurt", mat1};

  std::cout << b1;
  std::cout << b2;
  std::cout << b3;
  std::cout << s1;
  std::cout << s2;
  std::cout << s3;

  std::ostringstream str1;
  str1 << b1;
  std::string cstr1 = "Box default\nMaterial: def material\nPoints: (0|0|0) (0|0|0)\n\n";
  REQUIRE(str1.str() == cstr1);
  std::ostringstream str2;
  str2 << b2;
  std::string cstr2 = "Box default\nMaterial: def material\nPoints: (12|5|10) (10|1|5)\n\n";
  REQUIRE(str2.str() == cstr2);
  std::ostringstream str3;
  str3 << b3;
  std::string cstr3 = "Box Guntram\nMaterial: mat1\nPoints: (0|-2|8) (-3|-7|3)\n\n";
  REQUIRE(str3.str() == cstr3);
  std::ostringstream str4;
  str4 << s1;
  std::string cstr4 = "Sphere default\nMaterial: def material\nMiddle: (0|0|0) Radian: 10\n\n";
  REQUIRE(str4.str() == cstr4);
  std::ostringstream str5;
  str5 << s2;
  std::string cstr5 = "Sphere default\nMaterial: def material\nMiddle: (1.5|5.3|2.7) Radian: 4.51\n\n";
  REQUIRE(str5.str() == cstr5);
  std::ostringstream str6;
  str6 << s3;
  std::string cstr6 = "Sphere Kurt\nMaterial: mat17|0.7]\nMiddle: (3|1|5) Radian: 21\n\n";
  REQUIRE(str6.str() == cstr6);
}


TEST_CASE("intersect_ray_sphere", "[intersect]") {
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
  bool b = hp.cut;
  float d = hp.cdist;
  REQUIRE(d == Approx(4.0f));
  REQUIRE(b == true);

  //if radian is equal to zero
  Ray r2 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f}};
  Sphere c2 {{0.0f, 0.0f, 1.0f}, 0.0f};
  hp = c2.intersect(r2);
  d = hp.cdist;
  b = hp.cut;
  REQUIRE(d == Approx(1.0f)); 
  REQUIRE(b == true);

  //not intersecting
  Ray r3 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f}};
  Sphere c3 {{0.0f, 0.1f, 1.0f}, 0.0f};
  hp = c3.intersect(r3);
  d = hp.cdist;
  b = hp.cut;
  REQUIRE(d == Approx(-1.0f));
  REQUIRE(b == false);

  //negative radian
  Ray r4 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 1.0f}};
  Sphere c4 {{0.0f, 0.0f, 5.0f}, -1.0f};
  hp = c4.intersect(r4);
  b = hp.cut;
  d = hp.cdist;
  REQUIRE(d == Approx(4.0f));
  REQUIRE(b == true);

  //ray in opposite direction
  Ray r5 {{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, -1.0f}};
  Sphere c5 {{0.0f, 0.0f, 5.0f}, 1.0f};
  hp = c5.intersect(r5);
  b = hp.cut;
  d = hp.cdist;
  REQUIRE(d == Approx(-1.0f));
  REQUIRE(b == false);

  //ray starts somwhere inside the circle
  Ray r6 {{0.0f, 2.0f, 1.0f},{0.0f, 3.0f, -2.0f}};
  Sphere c6 {{5.0f, 2.0f, 2.0f}, 10.0f};
  hp = c6.intersect(r6);
  b = hp.cut;
  d = hp.cdist;
  REQUIRE(d == Approx(8.0655f));
  REQUIRE(b == true);

  //ray goes trough the exact middle of the sphere
  Ray r7 {{5.0f, 2.0f, 7.0f},{2.0f, 1.5f, 1.0f}};
  Sphere c7 {{19.0f, 12.5f, 14.0f}, 3.0f};
  hp = c7.intersect(r7);
  b = hp.cut;
  d = hp.cdist;
  REQUIRE(d == Approx(15.848f));
  REQUIRE(b == true);

  //ray touches the sphere
  Ray r8 {{-4.0f, 2.0f, 9.0f},{0.0f, 0.3f, 1.7f}};
  Sphere c8 {{-6.29999f, 3.89f, 19.71f}, 2.3f};
  hp = c8.intersect(r8);
  b = hp.cut;
  d = hp.cdist;
  auto n = hp.name;
  REQUIRE(d == Approx(10.87f));
  REQUIRE(b == true);
  REQUIRE(n == "Jeff");

  //ray almost touches the sphere bc 6.3f != 6.3
  Ray r9 {{-4.0f, 2.0f, 9.0f},{0.0f, 0.3f, 1.7f}};
  Sphere c9 {{-6.3f, 3.89f, 19.71f}, 2.3f};
  hp = c9.intersect(r9);
  b = hp.cut;
  d = hp.cdist;
  REQUIRE(d == Approx(-1));
  REQUIRE(b == false);
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