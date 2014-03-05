#include "CppUTest/CommandLineTestRunner.h"
#include "Settings.h"

TEST_GROUP(Settings) {
	void setup() {}
	void teardown() {}
};

TEST(Settings, shouldHaveDefaultValues) {

  Settings settings;
	CHECK_EQUAL(SETTINGS_DEFAULT_WIDTH, settings.width());
	CHECK_EQUAL(SETTINGS_DEFAULT_HEIGHT, settings.height());
  CHECK_EQUAL(SETTINGS_DEFAULT_NUM_SAMPLES, settings.numSamples());
  CHECK(settings.input());
  CHECK_EQUAL(0, strcmp(SETTINGS_DEFAULT_INPUT, settings.input()));
  CHECK(settings.output());
  CHECK_EQUAL(0, strcmp(SETTINGS_DEFAULT_OUTPUT, settings.output()));
  
}

TEST(Settings, shouldParseArgumentNumSamples) {

  char *args[] {
    "-n20"
  };

  settings.parse(1, args);

  CHECK_EQUAL(20, settings.numSamples());
 
}

TEST(Settings, shouldParseArgumentInputFile) {

  char *args[] {
    "-iScenes/hw2/test.ascii"
  };

  settings.parse(1, args);

  CHECK_EQUAL(0, strcmp(settings.input(), "Scenes/hw2/test.ascii"));
 
}

TEST(Settings, shouldParseArgumentOutputFile) {

  char *args[] {
    "-ooutput/test.png"
  };

  settings.parse(1, args);

  CHECK_EQUAL(0, strcmp(settings.output(), "output/test.png"));
 

}

TEST(Settings, shouldParseArgumentsWidthHeight) {

  char *args[] {
    "-r200:200"
  };

  settings.parse(1, args);

  CHECK_EQUAL(200, settings.width());
  CHECK_EQUAL(200, settings.height());
 

}
