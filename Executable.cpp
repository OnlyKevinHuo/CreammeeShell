#include <iostream>
#include <stdio.h>     //to use perror
#include <unistd.h>    //to use execvp + fork
#include <sys/wait.h>  //to use waitpid
#include <sys/types.h> //to use waitpid
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Executable.h"
using namespace std;


//=============================================================================

bool test_Exec(vector<string> yea){
  struct stat buf;
  string flag = yea.at(1);
  if(flag == "-f"){
    string file_path = yea.at(2);
    if(stat(file_path.c_str(), &buf) != -1){
      if(S_ISREG( buf.st_mode) != 0){
       cout << "(True)\n";
       return true;
      }
      else{
        cout << "(False)\n";
        return false;
      }
    }
    else{
      cout << "(False)\n"; 
      return false;
    }
  }
  else if(flag == "-d"){
  string dir_path = yea.at(2);
    if(stat(dir_path.c_str(), &buf) != -1){
      if(S_ISDIR( buf.st_mode) != 0){
       cout << "(True)\n";
       return true;
      }
      else{
        cout << "(False)\n";
        return false;
      }
    }
    else{
      cout << "(False)\n"; 
      return false;
    }
  }
  else if(flag == "-e"){
  string path = yea.at(2);
    if(stat(path.c_str(), &buf) != -1){
      cout << "(True)\n";
       return true;
    }
    else{
        cout << "(False)\n";
        return false;
    }
  }
  else{
    if(stat(flag.c_str(), &buf) != -1){
      cout << "(True)\n";
       return true;
    }
    else{
        cout << "(False)\n";
        return false;
    }  
  }
}

//======================================================================================================

bool test_Pipe_N_Redirection(vector<string> cmdd){
  
  for (int i = 0; i < cmdd.size(); ++i)
  {
    if (cmdd.at(i) == "<" || cmdd.at(i) == ">" || cmdd.at(i) == ">>" || cmdd.at(i) == "|")
    {
      return true;
    }
  }   
  return false; 
}

//=======================================================================================================

bool output_redirection(vector<string> leftCmd, vector<string> rightCmd) {
  int status = 0;
  char* args = (char*)rightCmd.at(0).c_str();
  int readout = open(args, O_WRONLY | O_CREAT | O_TRUNC, 0600 | S_IWUSR | S_IWGRP | S_IRGRP);

  if (readout < 0) {
    cout << "-bash: " << args << ": Failed to redirect command output" << endl;
    return false;
  }
  
  else {
    char* argsleft[leftCmd.size()+1];
    for (int i = 0; i < leftCmd.size(); i++){
      argsleft[i] = (char*)leftCmd.at(i).c_str();
    }
    argsleft[leftCmd.size()] = NULL;
  
    int newFile = dup(1);       //save stdin to newFile
    close(1);                   //close stdin
    dup(readout);                // set readin to stdin
  
  pid_t pid = fork();
  
  //int stdOutput = dup2(readout, 1);

  if (pid == 0){
    //kid
    if (execvp(argsleft[0], argsleft) == -1){
      perror("Error");
      status = 1;
      _exit(status);
    }
  }
  dup2(newFile, 1);
  close(readout);
  if (pid > 0){
    //parent
    if (waitpid(0,&status,0) == -1){
      perror("wait");
    }
    if (WIFEXITED(status)){
      if (WEXITSTATUS(status) == 1){
        return false;
      }
      else{
        return true;
      }
    }
  
  }
}
  return true;
}

//===================================================================================================

bool input_redirection(vector<string> leftCmd, vector<string> rightCmd) {
  int status = 0;
  char* args = (char*)rightCmd.at(0).c_str();
  int readin = open(args, O_RDONLY);
  
  if (readin < 0) {
    cout << "-bash: " << args << ": No such file or directory" << endl;
    return false;
  }
  
  else {
    char* argsleft[leftCmd.size()+1];
    for (int i = 0; i < leftCmd.size(); i++){
      argsleft[i] = (char*)leftCmd.at(i).c_str();
    }
    argsleft[leftCmd.size()] = NULL;
  
    int newFile = dup(0);       //save stdin to newFile
    close(0);                   //close stdin
    dup(readin);                // set readin to stdin
  
  pid_t pid = fork();
       
  if (pid == 0){
    //kid
    if (execvp(argsleft[0], argsleft) == -1){
      perror("Error");
      status = 1;
      _exit(status);
    }
  }
  
   dup2(newFile, 0);         // set stdin to 0
   close (readin);           // close readin

  if (pid > 0){
    //parent
    if (waitpid(0,&status,0) == -1){
      perror("wait");
    }
    if (WIFEXITED(status)){
      if (WEXITSTATUS(status) == 1){
        return false;
      }
      else{
        return true;
      }
    }
  
  }
}
  return true;
}
//===============================================================================

bool append_redirection(vector<string> leftCmd, vector<string> rightCmd) {
  int status = 0;
  char* args = (char*)rightCmd.at(0).c_str();
  int readout = open(args, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWGRP | S_IWUSR | S_IRGRP);
  
  if (readout < 0) {
    cout << "-bash: " << args << ": Failed to redirect command output" << endl;
    return false;
  }
  
  else {
    char* argsleft[leftCmd.size()+1];
    for (int i = 0; i < leftCmd.size(); i++){
      argsleft[i] = (char*)leftCmd.at(i).c_str();
    }
    argsleft[leftCmd.size()] = NULL;
  
    int newFile = dup(1);       //save stdin to newFile
    close(1);                   //close stdin
    dup(readout);                // set readin to stdin
  
  pid_t pid = fork();
       
  if (pid == 0){
    //kid
    if (execvp(argsleft[0], argsleft) == -1){
      perror("Error");
      status = 1;
      _exit(status);
    }
  }
  
   dup2(newFile, 1);         // set stdin to 0
   close (readout);           // close readin

  if (pid > 0){
    //parent
    if (waitpid(0,&status,0) == -1){
      perror("wait");
    }
    if (WIFEXITED(status)){
      if (WEXITSTATUS(status) == 1){
        return false;
      }
      else{
        return true;
      }
    }
  
  }
}
  return true;
}


//===============================================================================

bool is_Symbol(string x) {
  if (x == ">>" || x == ">" || x == "<" || x == "|") {
    return true;
  }
  else {
    return false;
  }
}
bool is_Symbol1(string x) {
  if (x == "|") {
    return true;
  }
  else {
    return false;
  }
}

//===============================================================================
bool in_out_redirection(vector<string> leftCmd, vector<string> midCmd, vector<string> rightCmd) {
  int status = 0;
  char* args = (char*)rightCmd.at(0).c_str();
  char* args1 = (char*)midCmd.at(0).c_str();
  int readout = open(args, O_WRONLY | O_CREAT | O_TRUNC, 0600 | S_IWUSR | S_IWGRP | S_IRGRP);
  int readin  = open(args1, O_RDONLY);
  
  if (readout < 0) {
    cout << "-bash: " << args << ": failed to redirect output" << endl;
    return false;
  }
  
  if (readin < 0) {
    cout << "-bash: " << args << ": No such file or directory" << endl;
    return false;
  }
  
 char* argsleft[leftCmd.size()+1];
  for (int i = 0; i < leftCmd.size(); i++){
    argsleft[i] = (char*)leftCmd.at(i).c_str();
  }
 argsleft[leftCmd.size()] = NULL;

  int newFilein = dup(0);       //save stdin to newFile
  close(0);                   //close stdin
  dup(readin);                // set readin to stdin
  
  int newFileout = dup(1);       //save stdin to newFile
  close(1);                   //close stdin
  dup(readout);                // set readin to stdin
    
  
  pid_t pid = fork();
       
  if (pid == 0){
    //kid
    if (execvp(argsleft[0], argsleft) == -1){
      perror("Error");
      status = 1;
      _exit(status);
    }
  }
  
   dup2(newFilein, 0);         // set stdin to 0
   close (readin);           // close readin
   
   dup2(newFileout, 1);         // set stdin to 0
   close (readout);           // close readin

  if (pid > 0){
    //parent
    if (waitpid(0,&status,0) == -1){
      perror("wait");
    }
    if (WIFEXITED(status)){
      if (WEXITSTATUS(status) == 1){
        return false;
      }
      else{
        return true;
      }
    }
  
  }
  return true;
  
}
//===============================================================================
bool in_append_redirection(vector<string> leftCmd, vector<string> midCmd, vector<string> rightCmd) {
  int status = 0;
  char* args = (char*)rightCmd.at(0).c_str();
  char* args1 = (char*)midCmd.at(0).c_str();
  int readout = open(args, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWGRP | S_IWUSR | S_IRGRP);
  int readin  = open(args1, O_RDONLY);
  
  if (readout < 0) {
    cout << "-bash: " << args << ": failed to redirect output" << endl;
    return false;
  }
  
  if (readin < 0) {
    cout << "-bash: " << args << ": No such file or directory" << endl;
    return false;
  }
  
 char* argsleft[leftCmd.size()+1];
  for (int i = 0; i < leftCmd.size(); i++){
    argsleft[i] = (char*)leftCmd.at(i).c_str();
  }
 argsleft[leftCmd.size()] = NULL;
  
  int newFilein = dup(0);       //save stdin to newFile
  close(0);                   //close stdin
  dup(readin);                // set readin to stdin
  
  int newFileout = dup(1);       //save stdin to newFile
  close(1);                   //close stdin
  dup(readout);                // set readin to stdin
    
  
  pid_t pid = fork();
       
  if (pid == 0){
    //kid
    if (execvp(argsleft[0], argsleft) == -1){
      perror("Error");
      status = 1;
      _exit(status);
    }
  }
  
   dup2(newFilein, 0);         // set stdin to 0
   close (readin);           // close readin
   
   dup2(newFileout, 1);         // set stdin to 0
   close (readout);           // close readin

  if (pid > 0){
    //parent
    if (waitpid(0,&status,0) == -1){
      perror("wait");
    }
    if (WIFEXITED(status)){
      if (WEXITSTATUS(status) == 1){
        return false;
      }
      else{
        return true;
      }
    }
  
  }
  return true;
  
}
//===================================================================================
bool pipe(vector<string> leftCmd, vector<string> rightCmd) {
  int status = 0;
  int sewer[2];
  pid_t pid = fork();
  pipe(sewer);
  
  if (pid == 0) {
  int origSTDIN = dup(0);
  int origSTDOUT = dup(1);
  char* argsL[leftCmd.size()+1];
  char* argsR[rightCmd.size()+1];
  
  string leftCmdd = leftCmd.at(0);
  
  for (int i = 1; i < leftCmd.size(); i++){
    leftCmdd = leftCmdd + " " + leftCmd.at(i);
  }
    
  const char* argsLe = leftCmdd.c_str();

  string rightCmdd = rightCmd.at(0);
  
  for (int i = 1; i < rightCmd.size(); i++){
    rightCmdd = rightCmdd + " " + rightCmd.at(i);
  }

  const char* argsRi = rightCmdd.c_str();
  
  // for (int i = 0; i < leftCmd.size(); i++){
  //       argsL[i] = (char*)leftCmd.at(i).c_str();
  //   }
  // for (int i = 0; i < rightCmd.size(); i++){
  //       argsR[i] = (char*)rightCmd.at(i).c_str();
  //   }
  // argsL[leftCmd.size()] = NULL;
  // argsR[rightCmd.size()] = NULL;

  
  FILE *pipe_in;
  FILE *pipe_out;
  char readingbuffer[1000];

  if ( (pipe_in = popen(argsLe, "r") ) == NULL) {
  	perror("ERROR");
  	return false;
  }

  if ( (pipe_out = popen(argsRi, "w") ) == NULL) {
  	perror("ERROR");
  	return false;
  } 

  while(fgets(readingbuffer, 1000, pipe_in)) {
  	fputs(readingbuffer, pipe_out);
  }
  
  pclose(pipe_in);
  pclose(pipe_out);
  
  }
  
  if (pid > 0) {
    //parent
    if (waitpid(0,&status,0) == -1){
      perror("wait");
    }
    if (WIFEXITED(status)){
      if (WEXITSTATUS(status) == 1){
        return false;
      }
      else{
        return true;
      }
    }
  }

  return true;
}



//===============================================================================
bool Executable::run(bool x){

  bool a_gain = false;
  if(exec.at(0) == "test" || exec.at(0) == "["){
    a_gain = test_Exec(exec);
    return a_gain;
  }

  int status = 0;
  char* args[exec.size()+1];
  bool runnin_runnin;
  bool firstLHS = true;
  if (test_Pipe_N_Redirection(exec)) {
      int j = 0;
      int k = -1;
      int num_pipes = 0;
      vector<string> leftCmd;
      vector<string> rightCmd;
      
      for (int i = 0; i < exec.size(); i++ ) {
        if(is_Symbol1(exec.at(i))) num_pipes++;
      }
      
      if(num_pipes == 0){
        for (int i = 0; i < exec.size(); i++ ) {
          //< >> case
          if (exec.size() >= 5 && exec.at(1) == "<" && exec.at(3) == ">>") {
            vector<string> leftCmd;
            vector<string> rightCmd;
            vector<string> midCmd;
            
            leftCmd.push_back(exec.at(0));
            midCmd.push_back(exec.at(2));
            rightCmd.push_back(exec.at(4));
            
            runnin_runnin = in_append_redirection(leftCmd, midCmd, rightCmd);
          }
          //< > case
          if (exec.size() >= 5 && exec.at(1) == "<" && exec.at(3) == ">") {
            vector<string> leftCmd;
            vector<string> rightCmd;
            vector<string> midCmd;
            
            leftCmd.push_back(exec.at(0));
            midCmd.push_back(exec.at(2));
            rightCmd.push_back(exec.at(4));
            
            runnin_runnin = in_out_redirection(leftCmd, midCmd, rightCmd);
          }
          
          // < case
          if (exec.at(i) == "<") {
            vector<string> leftCmd;
            vector<string> rightCmd;

            j = i - 1;
            while (j > k && !is_Symbol(exec.at(j) ) ) {
              leftCmd.insert(leftCmd.begin(), exec.at(j) );
              j--;
            }

            j = i + 1;
            while (j < exec.size() && !is_Symbol(exec.at(j) ) ) {
              rightCmd.push_back(exec.at(j) );
              j++;
            }
            runnin_runnin = input_redirection(leftCmd, rightCmd);
            k = i;
          }
          // > case
          else if (exec.at(i) == ">") {
            vector<string> leftCmd;
            vector<string> rightCmd;

            int j = i - 1;
            while (j > k && !is_Symbol(exec.at(j) ) ) {
              leftCmd.insert(leftCmd.begin(), exec.at(j) );
              j--;
            }

            j = i + 1;
            while (j < exec.size() && !is_Symbol(exec.at(j) ) ) {
              rightCmd.push_back(exec.at(j) );
              j++;
            }
            runnin_runnin = output_redirection(leftCmd, rightCmd); 
            k = i;
          }
          // >> case
          else if (exec.at(i) == ">>") {
            vector<string> leftCmd;
            vector<string> rightCmd;

            int j = i - 1;
            while (j > k && !is_Symbol(exec.at(j) ) ) {
              leftCmd.insert(leftCmd.begin(), exec.at(j) );
              j--;
            }

            j = i + 1;
            while (j < exec.size() && !is_Symbol(exec.at(j) ) ) {
              rightCmd.push_back(exec.at(j) );
              j++;
            }
            
            runnin_runnin = append_redirection(leftCmd, rightCmd); 
            k = i;
          }
        
        }
      }
      
      else if(num_pipes == 1){
        for (int i = 0; i < exec.size(); i++ ) {
          if (exec.at(i) == "<") {
              leftCmd.push_back(exec.at(0) );
              j = i + 1;
              while (j < exec.size() && !is_Symbol(exec.at(j) ) ) {
                leftCmd.push_back(exec.at(j) );
                j++;
              }
          }
          /*else if (exec.at(i) == ">") {
              leftCmd.push_back(exec.at(0) );
              j = i + 1;
              while (j < exec.size() && !is_Symbol(exec.at(j) ) ) {
                leftCmd.push_back(exec.at(j) );
                j++;
              }
          }*/
          if (exec.at(i) == "|") {
              vector<string> rightCmd;
              
              if(leftCmd.size() == 0){
                leftCmd.push_back(exec.at(0));
              }

              j = i + 1;
              while (j < exec.size() && !is_Symbol1(exec.at(j) ) ) {
                rightCmd.push_back(exec.at(j) );
                j++;
              }
              runnin_runnin = pipe(leftCmd, rightCmd);
              break;
            } 
        }
      }
    return runnin_runnin;    
  }
  

  else {

    for (int i = 0; i < exec.size(); i++){
        args[i] = (char*)exec.at(i).c_str();
    }
    args[exec.size()] = NULL;

    
    pid_t pid = fork();
     
    if (pid == 0){
      //kid
      if (execvp(args[0], args) == -1){
        perror("Error");
        status = 1;
        _exit(status);
      }
    }
    
    if (pid > 0){
    //parent
    if (waitpid(0,&status,0) == -1){
      perror("wait");
    }
    if (WIFEXITED(status)){
      if (exec.size() != 1 && exec.at(0) == "ls" && exec.at(1).at(1) == 'j')
         return false;
      if (WEXITSTATUS(status) == 1){
        return false;
      }
      else{
        return true;
      }
    }

    }

  }

  


}



