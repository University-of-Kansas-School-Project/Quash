#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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

bool Quash::ChangeDir(std::string dir) {

}

bool Quash::Run(std::string programPath,  bool isBackgroundProcess, std::string programArgs[]) {
  pid_t p_id;
  p_id = fork();
  /*int size = *(&programArgs + 1) - programArgs;
  char * const args[size+1];
  for(int i =0; i<size; i++){
    args[i] = programArgs[i].c_str();
  }

//sprintf()
 char args[size+1];
  for(int lcv; lcv < size+1; lcv++) {
    // args[lcv] = new char[programArgs[lcv].size()];
    args[lcv] = programArgs
  }
  args[size] = NULL;*/
  //char * c[] = {programArgs[i].c_str(), NULL};
  if(p_id < 0){
    fprintf(stderr, "Error in Fork\n");
    return false;
  }
  //Run program with no arguments
  if(programArgs == NULL) {
    // In child process
    if(p_id == 0){
      //execv(programPath.c_str(), &args);
      fprintf(stdout, "In child process without arguments\n");
    }
  }
  //Run program with arguments
  else {
    if(p_id == 0)
      fprintf(stdout, "In child process with arguments\n");
  }
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
