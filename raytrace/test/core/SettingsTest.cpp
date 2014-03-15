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
	CHECK_EQUAL(SETTINGS_DEFAULT_VALIAS, settings.valias());
	CHECK_EQUAL(SETTINGS_DEFAULT_HALIAS, settings.halias());
  CHECK_EQUAL(SETTINGS_DEFAULT_NUM_SAMPLES, settings.numSamples());
  CHECK(settings.input());
  CHECK_EQUAL(0, strcmp(SETTINGS_DEFAULT_INPUT, settings.input()));
  CHECK(settings.output());
  CHECK_EQUAL(0, strcmp(SETTINGS_DEFAULT_OUTPUT, settings.output()));
	CHECK_EQUAL(SETTINGS_DEFAULT_NUM_THREADS_N, settings.numThreadsN());
	CHECK_EQUAL(SETTINGS_DEFAULT_NUM_THREADS_M, settings.numThreadsM());
  
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

TEST(Settings, shouldParseArgumentsForAntiAliasing) {

  char *args[] {
    "-a2:4"
  };

  settings.parse(1, args);

  CHECK_EQUAL(2, settings.valias());
  CHECK_EQUAL(4, settings.halias());
 

}


TEST(Settings, shouldDefaultToNotUsingThreads) {

  Settings settings;

  char *args[] {
    "-a2:4"
  };

  settings.parse(1, args);

  CHECK( !settings.useThreads() );
 

}

TEST(Settings, providingThreadNumParameterShouldSwitchUseThreads) {

  Settings settings;

  char *args[] {
    "-t2:4"
  };

  settings.parse(1, args);

  CHECK( settings.useThreads() );
 

}

TEST(Settings, shouldGetThreadCountsFromThreadParameter) {

  char *args[] {
    "-t5:4"
  };

  settings.parse(1, args);

  CHECK_EQUAL( 5, settings.numThreadsN() );
  CHECK_EQUAL( 4, settings.numThreadsM() );
 
}

TEST(Settings, environmentMapShouldBeNULLWhenNotDefined) {

  Settings settings;

  char *args[] {
    "-t5:4"
  };

  settings.parse(1, args);

  CHECK( settings.environmentMap() == 0 );
 
}

TEST(Settings, shouldSetEnvironmentMap) {

  char *args[] {
    "-etest.png"
  };

  settings.parse(1, args);

  CHECK( strcmp(settings.environmentMap(), "test.png") == 0 );
 
}

TEST(Settings, progressShouldDefaultToFalse) {

  Settings settings;
  CHECK( !settings.progress() );
 
}

TEST(Settings, shouldParseProgress) {

  char *args[] {
    "-p"
  };

  settings.parse(1, args);

  CHECK( settings.progress() );
 
}
