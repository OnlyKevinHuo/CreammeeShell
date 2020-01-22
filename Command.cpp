#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unistd.h> 
#include <stdio.h>
#include <string.h>
#include "../header/Juat.h"
#include "../header/Executable.h"
#include "../header/SemiColon.h"
#include "../header/OrStrat.h"
#include "../header/AndStrat.h"

using namespace std;


Command::Command(){
    this->root = NULL;
    this->power = NULL;
}
//---------------------------------------------------------------------------

void Command::start_Command_prompt(){
    cout << "$ ";
}

//--------------------------------------------------------------------------------------
bool printInorder(struct Node* node) 
{ 
    if (node == NULL) 
        return true; 
  
    /* first recur on left child */
    printInorder(node->left); 
  
    /* then print the data of node */
    if (node->j->getstring() == "exit") return false;
    
    if (node->getIsRoot()){
        if (node->getParent() != NULL){
            node->getParent()->setBool(node->j->run(true));
            return true;
        }
        else {
            node->j->run(true);
            return true;
        }
    }
    else {
        if (node->getIsConnector() && node->j->run(node->successful() ) ) 
        {
            if (node->right->j->getstring() == "exit") 
                return false;
            
            printInorder(node->right);
        }
        
        else if (!node->getIsConnector())
        {
            if(node->getParent() != NULL)
            {
                node->getParent()->setBool(node->j->run(true));
                return true;
            }
            else 
            {
                node->j->run(true);
                return true;
            }
        }
            
        if (node->getParent() == NULL) 
            return true;
    }
} 

//---------------------------------------------------------------------------------------------------------
bool printPostfixTreeInOrder(Node* node) 
{
    if (node == NULL) 
        return true; 
  
    /* first recur on left child */
    printInorder(node->left); 
  
    /* then print the data of node */
    if (node->getIsRoot()){
        cout << "ISROOT" << endl;
        if (node->j->getstring() == "exit") return false;
        if (node->getParent() != NULL){
            node->getParent()->setBool(node->j->run(true));
            cout << "here!!!!!!!!!!!!" << endl;
        }
        else {
            cout << "IDUNNO" << endl;
            node->j->run(true);
            return true;
        }
    }
    else {
        cout << "HERE?" << endl;
        if (node->j->run(node->successful())){
            if(node->getParent() != NULL){
                if (node->right->j->getstring() == "exit") return false;
                node->getParent()->setBool(node->right->j->run(true));
            }
            else {
                if (node->right->j->getstring() == "exit") return false;
                node->right->j->run(true);
                return true;
            }
        }
                if (node->getParent() == NULL) return true;
    }
    
}
//----------------------------------------------------------------------------------------------------------

vector< vector<string> > infixToPostfix(vector< vector<string> > listy){
    stack < vector<string> > s;
    vector< vector<string> > postFix;

    for (int i = 0; i < listy.size(); i++){
        string firstString = listy.at(i).at(0);

        if (firstString != "&&" && firstString != "||" && firstString != ";" && firstString != "(" && firstString != ")" ) {
            postFix.push_back(listy.at(i));
        }

        else if (firstString == "&&" || firstString == "||" || firstString == ";") {

            if (s.empty() ) {
                s.push(listy.at(i) );
                continue;
            }

            else if (s.top().at(0) != "(" ) {
                postFix.push_back(s.top());
                s.pop();
            }
            s.push(listy.at(i));
        }

        else if (firstString == "(") {
            s.push(listy.at(i));
        }

        else if (firstString == ")") {
             while (s.top().at(0) != "(") {
                postFix.push_back(s.top());
                s.pop();
             }
             s.pop();
        }
    }
    while (!s.empty()) {
        postFix.push_back(s.top());
        s.pop();
    }
    
    return postFix;
}
//-------------------------------------------------------------------------------------------
Node* createInfixTree (vector<vector<string> > commandList) {
    
    bool isConnector = false;
    bool firstNode = true;
    Node* root;
    Node* last;
    
    for (int i = 0; i < commandList.size(); i++){
        Juat* newJuat;
        for(int j = 0; j < commandList.at(i).size(); j++){
            if (commandList.at(i).at(j) == ";"){
                newJuat = new SemiColon;
                isConnector = true;
            }
            else if (commandList.at(i).at(j) == "&&"){
                newJuat = new AndStrat;
                isConnector = true;
            }
            else if (commandList.at(i).at(j) == "||"){
                newJuat = new OrStrat;
                isConnector = true;
            }
            else {
                newJuat = new Executable(commandList.at(i));
                isConnector = false;
            }
            if (firstNode){
                  Node* current = new Node(NULL, NULL, NULL, newJuat, true);
                  current->setRoot();
                  firstNode = false;
                  root = current;
            }
            else if (isConnector){
                Node* current = root;
                Node* next = new Node(current, NULL, NULL, newJuat, true);\
                current->setParent(next);
                root = next;
            }
            else {
                Node* current = root;
                Node* next = new Node(NULL, NULL, current, newJuat, true);
                current->setright(next);
            }
            
        }
    }
    return root;
}
//-------------------------------------------------------------------------------------------
Node* createPostfixTree(vector<vector<string> > listy) {
    stack <Node*> creator;
    while (!creator.empty()){
        creator.pop();
    }
    
    bool first = true;
    bool isConnector = false;
    for (int i = 0; i < listy.size(); i++){
        Juat* newJuat;
        string firstString = listy.at(i).at(0);
        
        if (firstString == ";") {
            newJuat = new SemiColon;
            isConnector = true;
        }
        else if (firstString == "&&") {
            newJuat = new AndStrat;
            isConnector = true;
        }
        else if (firstString == "||") {
            newJuat = new OrStrat;
            isConnector = true;
        }
        else {
            newJuat = new Executable(listy.at(i));
            isConnector = false;
        }

        if (isConnector){
            Node* next = new Node(NULL, NULL, NULL, newJuat, true);
            next->setConnector(true);
            if (creator.size() < 2){
                return NULL;
            }
            else {
                next->right = creator.top();
                creator.pop();
                next->left = creator.top();
                creator.pop();
                creator.push(next);
                next->left->setParent(next);
                next->right->setParent(next);
            }
        }
        else {
            Node* next = new Node(NULL, NULL, NULL, newJuat, true);
            next->setConnector(false);
            creator.push(next);
            if (first){
                next->setRoot();
                first = false;
            }
        }
    }
    
    Node* root = creator.top();
    creator.pop();
    while (!creator.empty()){
        cout << "Something is wrong" << endl;
    }
    
    return root;
}

//--------------------------------------------------------------------------------------------

bool Command::run(bool x) {
    bool again = true;
    vector< vector<string> > commandList;
    vector<string> unfilteredCommand;
    string userCommand;

    this->start_Command_prompt();
    getline(cin,userCommand);
    
    string exitt = userCommand.substr(0,4);
    if (exitt == "exit"){
            return false;
    }
    
    
    string originalCommand = userCommand;
    int numBefore = originalCommand.size();
    userCommand = userCommand.substr(0, userCommand.find(" #"));
    int numAfter = userCommand.size();
    
    
    if (numBefore > numAfter) {
        int numQuotes= 0;
        for (int i = 0; i < numAfter; i++){
            if (originalCommand.at(i) == '"'){
                numQuotes++;
            }
        }
        if (numQuotes % 2 == 1){
            userCommand = originalCommand;
        }
    }
    
    if (userCommand.empty() || userCommand.at(0) == '#'){
        return true;
    }

    int numQuotes = 0;
    for (int i = 0; i < userCommand.size(); ++i)
    {
        if (userCommand.at(i) == '"')
            numQuotes++;
    }

    if (numQuotes % 2 != 0)
    {
        cout << "Error: uneven number of quotations" << endl;
        return true;
    }

    int numLeftParen = 0;
    int numRightParen = 0;
    for (int i = 0; i < userCommand.size(); ++i)
    {
        if (userCommand.at(i) == '(')
        {
            numLeftParen++;
        }
        else if (userCommand.at(i) == ')')
        {
            numRightParen++;
        }
    }

    if (numLeftParen != numRightParen)
    {
        cout << "Error: uneven number of parenthesis" << endl;
        return true;
    }
    
    char* point = (char*)userCommand.c_str();
    char* pch;
    pch = strtok (point," ");
    
    bool prevConnector = false;
    bool firstEntry = true;
    bool semiColonExists = false;
    bool commandExists = true;
    bool leftParenExists = false;
    bool rightParenExists = false;
    bool doubleConnector = false;
    bool prevRightParen = false;
    bool prevCommand = false;
    bool leftQuotationExists = false;

    
    vector<string> andVect(1, "&&");
    vector<string> orVect(1, "||");
    vector<string> semiVect(1, ";");
    vector<string> leftParen(1, "(");
    vector<string> rightParen(1, ")");

    while (pch != NULL)
    {
        char lastChar = pch[strlen(pch)-1];
        char firstChar = pch[0];
        string command = pch;

        if (firstEntry)
        {
            if ( command == ";" ||  command == "&&" || command == "||")         //if the user command start with a connector stop executung 
            {
                cout << "-bash: syntax error near unexpected token '" << command << "'" << endl;
                return true;
            }
            
            if (firstChar == '(')
            {
                while (firstChar == '(')
                {
                    command = command.substr(1,command.size());
                    commandList.push_back(leftParen);
                    firstChar = command.at(0);
                }
                prevConnector = true;
                leftParenExists = true;
                commandExists = true;
                prevCommand = false;
            }
            
            if (lastChar == ')'){
                rightParenExists = true;
            }
            
            if (lastChar == ';')
            {
                semiColonExists = true;
                commandExists = true;
                prevConnector = true;
                command = command.substr(0,command.size()-1);
            }

            string commandCopy = command;
            if (rightParenExists){
                char lastCharCopy = commandCopy.at(commandCopy.size()-1);

                while (lastCharCopy == ')'){
                    commandCopy = commandCopy.substr(0,commandCopy.size()-1);
                    lastCharCopy = commandCopy.at(commandCopy.size()-1);
                }
            }

            if (commandCopy.size() != 0){
                vector<string> temp;
                temp.push_back(commandCopy);
                commandList.push_back(temp);
                prevCommand = true;
                prevConnector = false;
            }            

            if (semiColonExists)
            {
                commandList.push_back(semiVect);
                semiColonExists = false;
                prevCommand = false;
                prevConnector = true;
            }
            
            if (rightParenExists)
            {
                while (lastChar == ')')
                {
                    command = command.substr(0,command.size()-1);
                    commandList.push_back(rightParen);
                    lastChar = command.at(command.size()-1);                
                }
                prevCommand = false;
                prevConnector = true;
                rightParenExists = false;
            }

            firstEntry = false;
        }
        
        else 
        {
            if (!leftQuotationExists)
            {

                if (firstChar == '(' && prevConnector || firstChar == '(' && commandList.size() == 1)              //For a left parenthesis to be valid the previous node must be a connector
                {
                    while (firstChar == '(')
                    {
                        command = command.substr(1,command.size());
                        commandList.push_back(leftParen);
                        firstChar = command.at(0);
                    }
                    prevConnector = true;
                    leftParenExists = true;
                    commandExists = true;
                    prevCommand = false;
                }

                if (lastChar == ';'){
                    if (prevConnector && command.size() == 1 && !leftParenExists && (prevRightParen && prevConnector)){         //a connector cannot follow another connector
                        doubleConnector = true;
                    } 
                    else {
                        command = command.substr(0,command.size()-1);
                        semiColonExists = true;
                        commandExists = true;
                    }
                }
                else if(command == "&&"){
                    if (prevConnector && !leftParenExists  && (prevRightParen && prevConnector)){                                  //a connector cannot follow another connector
                        doubleConnector = true;
                    }
                    else {
                        commandList.push_back(andVect);
                        prevConnector = true;
                        commandExists = false;
                        prevCommand = false;
                    }
                }
                else if(command == "||"){
                    if (prevConnector && !leftParenExists && (prevRightParen && prevConnector)){                                     //a connector cannot follow another connector
                        doubleConnector = true;
                    }         
                    else {
                        commandList.push_back(orVect);
                        prevConnector = true;
                        commandExists = false;        
                        prevCommand = false;
                    }      
                }

                if (doubleConnector)
                {
                    cout << "-bash: syntax error near unexpected token '" << command << "'" << endl;
                    doubleConnector = false;
                    return true;               
                }
            }

            if (!leftQuotationExists && commandExists && prevConnector){
                if (lastChar == ')') {            //For a right parenthesis to be valid the previous node cannot be a connector
                    rightParenExists = true;  
                    leftParenExists = false;
                }

                while (firstChar == '"') {
                    if (command.size() > 1){
                        command = command.substr(1,command.size());
                    }
                    else if (command.size() == 1){
                        command = "";
                        firstChar = '0';
                        lastChar = '0';
                    }
                    if(command.size() !=  0) {
                            firstChar = command.at(0);
                            lastChar = command.at(command.size()-1);                     
                    }
                    if (!leftQuotationExists) {
                        leftQuotationExists = true;
                    }
                    else {
                        leftQuotationExists = false;
                    }
                }

                while (lastChar == '"'){
                    if (command.size() > 1){
                        command = command.substr(0,command.size()-1);
                    }
                    else if (command.size() == 1){
                        command = "";
                        firstChar = '0';
                        lastChar = '0';
                    }
                    if(command.size() !=  0) {
                        lastChar = command.at(command.size()-1);
                    }
                    if (!leftQuotationExists) {
                        leftQuotationExists = true;
                    }
                    else {
                        leftQuotationExists = false;
                    }                                   
                }         

                string commandCopy = command;
                if (rightParenExists){
                    char lastCharCopy = commandCopy.at(commandCopy.size()-1);

                    while (lastCharCopy == ')'){
                        commandCopy = commandCopy.substr(0,commandCopy.size()-1);
                        lastCharCopy = commandCopy.at(commandCopy.size()-1);
                    }
                }
                
                vector<string> temp;

                if (commandCopy.size() != 0){
                    temp.push_back(commandCopy);
                    commandList.push_back(temp);
                    prevConnector = false;
                    prevCommand = true;
                }
                
                if (rightParenExists)
                {
                    while (lastChar == ')'){
                        command = command.substr(0,command.size()-1);
                        commandList.push_back(rightParen);
                        lastChar = command.at(command.size()-1);
                    }
                    prevConnector = true;
                    rightParenExists = false;
                    prevCommand = false;
                }

                if (semiColonExists){
                    commandList.push_back(semiVect);
                    prevConnector = true;
                    prevCommand = false;
                    semiColonExists = false;
                }
                else {
                    prevConnector = false;
                }
            }
            
            else if(leftQuotationExists || prevCommand || commandExists && !prevConnector || commandExists && rightParenExists || commandExists && leftParenExists)
            {
                if (lastChar == ')') {          
                    rightParenExists = true;  
                }

                
                while (firstChar == '"') {
                    if (command.size() > 1){
                        command = command.substr(1,command.size());
                    }
                    else if (command.size() == 1){
                        command = "";
                        firstChar = '0';
                        lastChar = '0';
                    }
                    if(command.size() !=  0) {
                        firstChar = command.at(0);
                        lastChar = command.at(command.size()-1);
                    }
                    if (!leftQuotationExists) {
                        leftQuotationExists = true;
                    }
                    else {
                        leftQuotationExists = false;
                    }
                }

                while (lastChar == '"'){
                    if (command.size() > 1){
                        command = command.substr(0,command.size()-1);
                    }
                    else if (command.size() == 1){
                        command = "";
                        firstChar = '0';
                        lastChar = '0';
                    }
                    if(command.size() !=  0) {
                        lastChar = command.at(command.size()-1); 
                    }
                    if (leftQuotationExists) {
                        leftQuotationExists = false;
                    }
                    else {
                        leftQuotationExists = true;
                    }                                   
                }  

                string commandCopy = command;
                if (rightParenExists){
                    char lastCharCopy = commandCopy.at(commandCopy.size()-1);

                    while (lastCharCopy == ')'){
                        commandCopy = commandCopy.substr(0,commandCopy.size()-1);
                        lastCharCopy = commandCopy.at(commandCopy.size()-1);
                    }
                }

                if (commandCopy.size() != 0){
                    commandList.at(commandList.size()-1).push_back(commandCopy);
                    prevConnector = false;
                    prevCommand = true;
                }

                if (rightParenExists)
                {
                    while (lastChar == ')'){
                        command = command.substr(0,command.size()-1);
                        commandList.push_back(rightParen);
                        lastChar = command.at(command.size()-1);
                    }
                    prevConnector = true;
                    rightParenExists = false;
                    leftParenExists = false;
                    prevRightParen = true;
                    prevCommand = false;
                }                
                
                if (semiColonExists){
                    commandList.push_back(semiVect);
                    prevConnector = true;
                    semiColonExists = false;
                    prevCommand = false;
                }
                else {
                    prevConnector = false;
                }
            }
        }
         pch = strtok (NULL," ");
         commandExists = true;
            
    }

    vector< vector<string> > postfixedCmdList = infixToPostfix(commandList);
    Node* root = createPostfixTree(postfixedCmdList);
    
    // for (int i = 0; i < postfixedCmdList.size(); i++){
    //     for(int j = 0; j < postfixedCmdList.at(i).size(); j++){
    //         cout << postfixedCmdList.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    
    

    again = printInorder(root);


        
  return again;
}
