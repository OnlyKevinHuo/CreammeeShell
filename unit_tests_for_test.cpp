#ifndef __UNIT_TESTS_FOR_TEST_CPP__
#define __UNIT_TESTS_FOR_TEST_CPP__
#include "../header/Connector.h"
#include "../header/AndStrat.h"
#include "../header/OrStrat.h"
#include "../src/SemiColon.cpp"
#include "../src/Executable.cpp"
#include "gtest/gtest.h"

TEST(Executable, multipleLine) {
   vector<string> commandLine;
		commandLine.push_back("test");
		commandLine.push_back("main.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif