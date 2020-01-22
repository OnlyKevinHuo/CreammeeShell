#ifndef __CONNECTOR_TESTS_CPP__
#define __CONNECTOR_TESTS_CPP__
#include "../header/Connector.h"
#include "../header/AndStrat.h"
#include "../header/OrStrat.h"
#include "../src/SemiColon.cpp"
#include "../src/Executable.cpp"
#include "gtest/gtest.h"

TEST(Connectors, Semi1) {
   bool runns = true;
   SemiColon* semi = new SemiColon();
   EXPECT_EQ(semi->run(runns),true);
   EXPECT_EQ(semi->getstring(),";");
}

TEST(Connectors, Semi2) {
   bool runns = false;
   SemiColon* semi = new SemiColon();
   EXPECT_EQ(semi->run(runns),true);
}

TEST(Connectors, And1) {
   bool runns = true;
   AndStrat* and1 = new AndStrat();
   EXPECT_EQ(and1->run(runns),true);
   EXPECT_EQ(and1->getstring(),"&&");
}

TEST(Connectors, And2) {
   bool runns = false;
   AndStrat* or1 = new AndStrat();
   EXPECT_EQ(or1->run(runns),false);
}

TEST(Connectors, Or1) {
   bool runns = false;
   OrStrat* or2 = new OrStrat();
   EXPECT_EQ(or2->run(runns),true);
   EXPECT_EQ(or2->getstring(),"||");
}

TEST(Executable, singleLine) {
   vector<string> commandLine;
		commandLine.push_back("ls");
		Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
   EXPECT_EQ(exec.getstring(),"ls");
}

TEST(Executable, multipleLine) {
   vector<string> commandLine;
		commandLine.push_back("pwd");
		commandLine.push_back("&&");
		commandLine.push_back("ls");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
   EXPECT_EQ(exec.getstring(),"pwd");
}

TEST(Executable_Test_Function, Exists1) {
    vector<string> commandLine;
		commandLine.push_back("test");
		commandLine.push_back("main.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

TEST(Executable_Test_Function, Exists2) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-e");
		commandLine.push_back("main.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

TEST(Executable_Test_Function, Exists3) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-e");
		commandLine.push_back("src/Executable.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

TEST(Executable_Test_Function, Exists4) {
    vector<string> commandLine;
		commandLine.push_back("test");
		commandLine.push_back("santa.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),false);
}

TEST(Executable_Test_Function, Exists5) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-e");
		commandLine.push_back("src/clause.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),false);
}

TEST(Executable_Test_Function, FileExists1) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-f");
		commandLine.push_back("main.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

TEST(Executable_Test_Function, FileExists2) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-f");
		commandLine.push_back("src/Executable.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

TEST(Executable_Test_Function, FileExists3) {
    vector<string> commandLine;
		commandLine.push_back("test");
    commandLine.push_back("-f");
		commandLine.push_back("TrueFreedom.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),false);
}

TEST(Executable_Test_Function, FileExists4) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-f");
		commandLine.push_back("header/TrumpsNoggin.cpp");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),false);
}

TEST(Executable_Test_Function, DirectoryExists1) {
    vector<string> commandLine;
    commandLine.push_back("test");
		commandLine.push_back("src");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

TEST(Executable_Test_Function, DirectoryExists2) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-d");
		commandLine.push_back("header");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),true);
}

TEST(Executable_Test_Function, DirectoryExists3) {
    vector<string> commandLine;
    commandLine.push_back("test");
    commandLine.push_back("-d");
		commandLine.push_back("unicorns");
   	Executable exec(commandLine);
  
   EXPECT_EQ(exec.run(true),false);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
