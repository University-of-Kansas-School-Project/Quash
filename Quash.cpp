#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

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

bool Quash::Pipe(std::string* leftProgram, std::string* rightProgram) {
  int p[2];
  std::cout<<" In pipe\n";
  if(pipe(p)<0){
    fprintf(stderr, "Error in Fork\n");
    return false;
  }
  pid_t p_id1, p_id2;
  int status;
  char * argsl[leftProgram->length()+1];
  for(int i =0; i<leftProgram->length(); i++){
    argsl[i] = const_cast<char *>(leftProgram[i].c_str());
  }

  argsl[leftProgram->length()] = NULL;

  char * argsR[rightProgram->length()+1];
  for(int i =0; i<rightProgram->length(); i++){
    argsR[i] = const_cast<char *>(rightProgram[i].c_str());
  }

  argsR[rightProgram->length()] = NULL;
  p_id1 = fork();
  if(p_id1 < 0){
    fprintf(stderr, "Error in Fork\n");
    return false;
  }
  if(p_id1 == 0){
    std::cout<<" In left\n";
    dup2(p[1], STDOUT_FILENO);
    close(p[0]);
    close(p[1]);
    //write(p[1], "main", 4);
    //std::cout<<"main";
    execvp(argsl[0], argsl);
  }

  p_id2 = fork();
  if(p_id2 < 0){
    fprintf(stderr, "Error in Fork\n");
    return false;
  }
  if(p_id2 == 0){
    std::cout<<" In right\n";
    dup2(p[0], STDIN_FILENO);
    close(p[0]);
    close(p[1]);
    execvp(argsR[0], argsR);
  }

  if ((waitpid(p_id1, &status, 0)) == -1) {
    fprintf(stderr, "Process 0 encountered an error. ERROR%d\n", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(p_id2, &status, 0)) == -1) {
    fprintf(stderr, "Process 1 encountered an error. ERROR%d\n", errno);
    return EXIT_FAILURE;
  }

}

//bool Quash::KillJob(int sigNum, int jobID) {
//
// }
