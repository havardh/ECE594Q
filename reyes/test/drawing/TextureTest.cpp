#include "CppUTest/CommandLineTestRunner.h"
#include "Texture.h"

TEST_GROUP(Texture) {
  void setup() {}
  void teardown() {}
};

TEST(Texture, shouldLoadATextureFromFile) {
  
	Texture texture("data/10x10.png");
  
}

TEST(Texture, shouldGetAPixel) {
  
	Texture texture("data/10x10.png");
  Color c = texture.get(0,0);
  
  CHECK_EQUAL(0, c.red);
  CHECK_EQUAL(0, c.green);
  CHECK_EQUAL(0, c.blue);

  c = texture.get(0.5,0.5);
  CHECK(0 != c.red);
  CHECK(0 != c.green);
  CHECK(0 != c.blue);


  c = texture.get(1,1);
  CHECK_EQUAL(100, c.red);
  CHECK_EQUAL(100, c.green);
  CHECK_EQUAL(100, c.blue);
  
}


// Should get pixel at (float,float)
