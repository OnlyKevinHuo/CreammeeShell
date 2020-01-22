#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h> 
#include <stdio.h>
#include <string.h>
#include "header/Juat.h"
#include "header/Executable.h"
#include "header/SemiColon.h"
#include "header/OrStrat.h"
#include "header/AndStrat.h"
#include "header/Command.h"
#include "src/Command.cpp"
#include "src/SemiColon.cpp"
#include "src/Executable.cpp"
using namespace std;


int main() {

Command* start = new Command;
bool weRun = true;
while(weRun){
weRun = start->run(true);
}
return 0;
}
