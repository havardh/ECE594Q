#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GTestConvertor.h"

int main(int ac, char* av[]) {
  GTestConvertor convertor;
  convertor.addAllGTestToTestRegistry();
  return CommandLineTestRunner::RunAllTests(ac, av);
}
