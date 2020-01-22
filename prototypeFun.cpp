#include <iostream>
#include <stdio.h>     //to use perror
#include <unistd.h>    //to use execvp + fork
#include <sys/wait.h>  //to use waitpid
#include <sys/types.h> //to use waitpid
#include <stdlib.h>

using namespace std;
//fork() => parent process returns its current process ID
//       - child process returns 0 as process ID
//		   - if fork fails it returns -1 then we do error checking : perror("fork");

//waitpid(pid_t pid, int *status, int options); =>
//			- if pid < -1 => wait for any child preoccess whose pid equals abs(pid) 
//			- if pid = -1 => wait for any child  process
//			- if pid = 0 => wait for any while process whose pid = calling process pid
//			- if pid > 0 => wait for child process whose pid = pid

//execvp(const char* file, char* const argv[]); =>
//			- returns only when error has occured: return -1 

int main(){

	char* args[3];
	
	string exec;
	string argList;
	int status;
	
	cout << "Enter a executable command" << endl;
	cin >> exec;

	cout << "Enter arguments" << endl;
	getline(cin,argList);
	cin.ignore();


	args[0] = (char*)exec.c_str();	
	if (argList.size() == 0){
		args[1] = NULL;
	} 
	else {
		args[1] = (char*)argList.c_str();
		args[2] = NULL;
	}
	

	pid_t pid = fork();
	
	if (pid == 0){
		//kid
		//cout << "child " << pid << endl;
		if (execvp(args[0], args) == -1){
			perror("exec");
		}
	}
	if (pid > 0){
		//parent		
		waitpid(-1,&status,0);
		//cout << "parent " << pid << endl;
	}
	cout << "finished" << endl;
	return 0;
}




//	int status;
//
//	if (pid == -1){
//		perror("fork");
//	}
//	if (pid == 0){
//		//kid process
//		cout << "child:" << pid << endl; 
//	}
//	if (pid > 0){
//		//parent process
//		//while(1);
//		waitpid(-1,&status,0);
//		cout << "parent:" << pid << endl;
//	}
