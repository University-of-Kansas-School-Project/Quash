#include <iostream>
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
bool Quash::SetPath(std::string path) {

}

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

//bool Quash::KillJob(int sigNum, int jobID) {
//
// }
