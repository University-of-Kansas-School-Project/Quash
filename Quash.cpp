#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "Quash.h"

//Constructor
Quash::Quash(std::string* p, std::string h, std::string pd) {
  path = p;
  home = h;
  pwd = pd;
}

//Member Functions
bool Quash::ChangeDir(const char* dir) {
  char* currDir;
  char* prevDir = getcwd(NULL, 1024);
  if(dir != NULL) {
    // std::cout << "Changing to Dir: " <<dir <<std::endl;
    if(chdir(dir) == -1) {
      fprintf(stderr, "Directory not found. Error: %d\n", errno);
      return false;
    }
    currDir = getcwd(NULL, 1024);
    setenv("PWD", currDir, 1);
    setenv("OLD_PWD", prevDir, 1);
  }
  else {
    chdir(getenv("HOME"));
    currDir = getcwd(NULL, 1024);
  }
  SetPwd(std::string(currDir));
  // std::cout <<"Current Working Directory: " <<currDir <<".\n";
  return true;
}

bool Quash::Run(std::string* programPath,  bool isBackgroundProcess, int c) {
  pid_t p_id;
  int status;
  p_id = fork();
  char * args[c+1];
  for(int i =0; i<c; i++){
    args[i] = const_cast<char *>(programPath[i].c_str());
  }

  args[c] = NULL;

  if(p_id < 0){
    fprintf(stderr, "Error in Fork\n");
    return false;
  }
  if(p_id == 0){
    execvp(args[0], args);
  }
  else if(!isBackgroundProcess)
    while (wait(&status) != p_id);

  return false;
}

void Quash::PrintJobs() {

}

bool Quash::WriteOut(std::string path) {

}

bool Quash::ReadIn(std::string path) {

}

bool Quash::Pipe(std::string leftProgram, std::string rightProgram) {

}

void Quash::Import(std::string inputFile) {
  // std::cout << "Importing file: " <<inputFile <<std::endl;
  std::list<std::list<std::string>*> cmds;
  std::ifstream fs(inputFile);

  char c;
  int numOfCmds = 0;
  std::string temp;
  std::list<std::string>* tempList = new std::list<std::string>;

  //Import cmds
  if (fs.is_open()) {
    while(fs.get(c)) {
      if (c != ' ' && c != '\n') {
        temp += c;
      }
      else if(c == ' ') {
        // std::cout << "Adding new arg to cmd list\n";
        tempList->push_back(temp);
        temp = "";
      }
      else if(c == '\n') {
        // std::cout <<"Import: Size of current cmd: " <<tempList->size() <<std::endl;
        tempList->push_back(temp);
        cmds.push_back(tempList);
        tempList = new std::list<std::string>;
        numOfCmds++;
        temp = "";
      }
    }
    fs.close();

    // std::cout <<"Number of Commands to run: " <<cmds.size() <<std::endl;

    for(int lcv = 0; lcv < numOfCmds; lcv++) {
      std::list<std::string>* currentCmd = cmds.front();

      // std::cout <<"Size of current cmd: " <<currentCmd->size() <<std::endl;

      std::string strArr[currentCmd->size()];
      std::list<std::string>::iterator it;
      int argCount = 0;
      for (it = currentCmd->begin(); it != currentCmd->end(); ++it){
        strArr[argCount] = *it;
        argCount++;
      }
      std::string bg = strArr[currentCmd->size()-1];
      bool isBackGnd = false;
      if(bg[bg.size()-1] == '&') {
        isBackGnd == true;
      }
      Run(strArr, isBackGnd, argCount);
      std::cout <<std::endl;
      cmds.pop_front();
    }
  }
  else {
    std::cout << "File Path: " <<inputFile <<" is an invalid path.\n";
  }
}
//bool Quash::KillJob(int sigNum, int jobID) {
//
// }
