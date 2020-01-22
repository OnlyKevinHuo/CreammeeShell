# CS 100 RShell Programming Project

> Author(s): Annie Wong (862047406), Kevin Huo (861152117)

> Spring 2019

# Introduction
Our program will replicate the functionality of a shell in a C++ executable environment. The design pattern that is used is the composite design pattern, which allows us to  break our program down into several primitive and composite classes. This pattern makes it so that user/client only has to be aware of and interact with a single object, which means that the user can be completely oblivious of the subclasses or objects connected to the root object (the object the client interacts with). This program will essentially take in a string as input which will be the shell command. No matter how long the command is or how many commands (separated by connectors) are in the string, the program must be able to evaluate it. Our program will break the string up push it into a vector while also differentiating between the executable + argument list, and the  connectors. So, the vector will be made up of two classes, the Executable class which will hold the executables and argument lists of the command and the Connector class which will hold the connectors of the command (if they exist). The interface contains two virtual functions, run and get_line which will be distinctly defined in both the Connector and Executable class, by use of polymorphism. These functions will process the inputs based on their class's specifications and all in all make it possible for the program to complete it's goal successfully. In the end, the composite design pattern and polymorphism make it so that our program takes on a tree-like structure. 

# UML Diagram
![alt text](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/blob/master/UML.PNG)

# Class Descriptions

## Juat
Juat is the abstract base class that the various children classes (primitive or composite) will inherit from. There are two public virtual functions that are necessary in most of the children classes. These classes will also be the extent in which the user will be able to interact with the system. The virtual bool run() function will return a boolean value because the boolean value will be used to determine whether or not the next command should run depending on the connector logic. Virtual string get_Line() is necessary for character/command input which will take place predominantly in the Command class (the composite class).

## Connector
The connector class will consist of the logic behind the three required connectors. The ; connector will always execute the following command. The || and && connectors are logic gates that determine whether a command is executed on the premise that the previous command succeeds or fails respectively. The run() function will have a string passed in. This string will be the connector that the run() function uses to determine what path of logic the following command will be executed in.

## Executable
The Executable class will be used to execute commands being input by the user. Both of the virtual functions from Juat will be implemented. The run() function will be passed the whole command string minus the connector. In the run() function, the executable will be parsed and the appropriate course of action will be decided. The argument_List portion of the string will then follow the course of execution. Also Includes function to handle input and output redirection and also piping. 

## Command
The Command class is the composite object that will hold the primitive classes and call any run() function from the primitives. The Command class will have two private data types that will be used to properly execute the user input. Bool runned is a boolean data variable that will reflect if the current command ran successfully. This boolean data variable enables for user inputs with multiple commands to utilize the success of each command to the following commands. There is a vector that consists of Juat* in order to collect the user input in a linear fashion. Command will have four functions. Two are the virtual functions inherited from Juat and two additional functions that will assist in properly executing the user environment and instructions. Bool get_runned is a getter function that will provide access to and set the private boolean runned variable. The get_runned function will be called within the overloaded connector run() function as it holds necessary data for determining the connector logic. The start_Command_Prompt() function will provide the starting point in which the user will understand when it is appropriate to input data. Functionally the start_Command_Prompt() will print the $ symbol as a signal to the user. The get_Line() function will collect the user input and parse the necessary strings into the composite vector. The bool run() function will be overloaded to handle the two primitive types, as in, they will call the run() functions of the primitive classes.

# Prototypes/Research
* While creating the prototype function we found that we can combine the functions waitpid(), execvp(), and fork() together to efficiently run shell functions without having to define each shell function ourself. 

* By itself, the fork function essentially creates a new process from the process that calls fork(). The new process is called the child process and the process that calls it is called the parent process. The child process continues to run the program starting from the line where fork is called. An important note is that the processes created by fork will run at the same time. Also fork() returns the process ID of the process that calls it.

* If waitpid() is called in a parent process, the parent process waits for the child process to finish. The first argument of waitpid determines what child process the parent process should wait for, the second argument stores the status of the process, and the third argument modified what waitpid does.

* And Execvp() essentially takes in the shell commands as an array of character and runs the command if it exists in a PATH environment. 

* In a normal shell the logic of the connectors work just as assignment 2 describes. ("If a command is followed by ;, then the next command is always executed; if a command is followed by &&, then the next command is executed only if the first one succeeds; if a command is followed by ||, then the next command is executed only if the first one fails.") 

* If "lss -a; ls" is typed in as a command then the shell will print out an error, but still continue to execute the second ls command.

* If "lss -a && ls" is typed in as a command then the shell will print out an error and not execute the following command.
* But if "ls -a && lss" is typed in as a command then the shell execute the first command and continue to execute the following command.

* If "lss -a || ls" is typed in as a command then the shell will print out an error, but still continue to execute the second ls command.
* But if If "ls -a || lss" is typed in as a command then the shell will successfully execute the first command and not try to execute the following command.


# Development and Testing Roadmap

* Create Juat Pure Virtual Class [ ]
  * Write Virtual bool run(string arg_list) [ ]
  * Write Virtual string get_Line(string input) [ ]
* Create Unit Testing for Executable Class [ ]
* Write the Executable Class
   * Write Virtual bool run(string arg_list) [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
   * Write Virtual string get_Line(string input) [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
* Create Unit Testing for Connector Class [ ]
* Write the Connector Class [ ]
  * Write Virtual bool run(string arg_list) [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
   * Write Virtual string get_Line(string input) [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
* Create Unit Testing for Command Class [ ] 
* Create the Command Class [ ]
  * Write start_Command_Prompt() [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
  * Write bool get_Runned() [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
  * Write Virtual bool run(string arg_list) [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
  * Write Virtual string get_Line(string input) [ ]
     * Perform Unit Test [ ]
     * Perform Integration Test [ ]
* Final Testing and Revisions [ ]    

# Issues 
* [Final Testing and Revisions](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/31)
* [Perform Integration test for Connector get_Line](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/30)
* [Perform Unit Test For Connector get_Line](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/29)
* [Write Connector string get_Line](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/28)
* [Perform Integration test for Command bool run](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/27)
* [Perform Unit test for Command bool run](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/26)
* [Write Command bool run](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/25)
* [Perform Integration test for get_Runned](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/24)
* [Perform Unit test for get_Runned](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/23)
* [Write bool get_Runned](https://github.com/cs100/spring-2019-assignment-stretchy_ice_cream/issues/22)



