#include <iostream>
#include <list>
#include <fstream>
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

  bgJobs = new std::list<Process*>;
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
  char * args[c+1];

  //Add Job to BgJobs if Background Process
  if(isBackgroundProcess) {
    std::string raw;
    for(int i = 0; i < c; i++) {
      raw += programPath[i] + ' ';
    }

    raw = raw.substr(0, raw.size()-2);
    programPath[c-1] = programPath[c-1].substr(0, programPath[c-1].size()-1);

    bgJobs->push_back(new Process(getpid(), "stopped", programPath, raw, c));
    std::cout << std::endl;
    std::cout <<'[' <<bgJobs->size() <<"] " <<getpid() <<" running in background\n";
    return true;
  }
  else {
    //std::cout << "->Running process: " <<programPath[0] <<std::endl;
    for(int i =0; i<c; i++){
      args[i] = const_cast<char *>(programPath[i].c_str());
    }

    args[c] = NULL;

    p_id = fork();

    if(p_id < 0){
      fprintf(stderr, "Error in Fork\n");
      return false;
    }
    if(p_id == 0){
      const char *p = GetPath()->c_str();
      char  pathenv[strlen(p) + sizeof("PATH=")];
      sprintf(pathenv, "PATH=%s", p);
      char *envp[] = {pathenv, NULL};
      execvpe(args[0], args, envp);
    }
    else if(!isBackgroundProcess)
      while (wait(&status) != p_id);

  }

  return true;
}

bool Quash::WriteOut(std::string* cmd, std::string path) {
// std::cout <<"In Write Out\n";

}

bool Quash::ReadIn(std::string cmd, std::string path) {
// std::cout <<"In Read In.\n";
// std::cout <<"Running cmd: " <<cmd <<" and with path: " <<path <<".\n";

std::list<std::list<std::string>*> args;
std::ifstream fs(path);

char c;
int numOfCmds = 0;
std::string temp;
std::list<std::string>* tempList = new std::list<std::string>;
tempList->push_back(cmd);
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
      args.push_back(tempList);
      tempList = new std::list<std::string>;
      tempList->push_back(cmd);

      numOfCmds++;
      temp = "";
    }
  }
  fs.close();

  for(int lcv = 0; lcv < numOfCmds; lcv++) {
    std::list<std::string>* currentCmd = args.front();

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
    args.pop_front();
  }
}
else {
  std::cout << "File Path: " <<path <<" is an invalid path.\n";
}

}

bool Quash::Pipe(std::string* leftProgram, std::string* rightProgram) {
  int p[2];
  std::cout<<" In pipe\n";
  if(pipe(p)<0){
    fprintf(stderr, "Error in Fork\n");
    return false;
  }
  const char *pt = GetPath()->c_str();
  char  pathenv[strlen(pt) + sizeof("PATH=")];
  sprintf(pathenv, "PATH=%s", pt);
  char *envp[] = {pathenv, NULL};
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
    close(p[0]);
    dup2(p[1], STDOUT_FILENO);
    close(p[1]);
    //write(p[1], "main", 4);
    //std::cout<<"main";
    if(execvpe(argsl[0], argsl, envp) < 0){
      fprintf(stderr, "Error in Exec\n");
      return false;
    }
  }
  if ((waitpid(p_id1, &status, 0)) == -1) {
    fprintf(stderr, "Process 0 encountered an error. ERROR%d\n", errno);
    return EXIT_FAILURE;
  }
  p_id2 = fork();
  if(p_id2 < 0){
    fprintf(stderr, "Error in Fork\n");
    return false;
  }
  if(p_id2 == 0){
    close(p[1]);
    std::cout<<" In right\n";
    std::cout<<argsR[1]<<std::endl;
    dup2(p[0], STDIN_FILENO);
    close(p[0]);
    if(execvpe(argsR[0], argsR, envp) < 0){
      fprintf(stderr, "Error in Exec\n");
      return false;
    }
  }
  if ((waitpid(p_id2, &status, 0)) == -1) {
    fprintf(stderr, "Process 1 encountered an error. ERROR%d\n", errno);
    return EXIT_FAILURE;
  }
  return true;
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

void Quash::ListJobs() {
  //std::cout <<"NUM OF JOBS: " <<bgJobs->size() <<std::endl;
  if(bgJobs->empty() == false) {
    std::list<Process*>::iterator process;
    int processIndex = 0;
    for (process = bgJobs->begin(); process != bgJobs->end(); ++process){
      Process * currProcess = *process;
      std::cout <<'[' <<processIndex+1 <<"]";
      if(processIndex == bgJobs->size()-2 && bgJobs->size() >= 2) {
        std::cout <<"- ";
      }
      else if(processIndex == bgJobs->size() - 1 && bgJobs->size() >= 2) {
        std::cout <<"+ ";
      }
      else if(processIndex == bgJobs->size()-1 && bgJobs->size() == 1) {
        std::cout <<"+ ";
      }
      std::cout <<currProcess->status <<"\t ";
      std::cout << currProcess->cmdRaw;
      processIndex++;
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  else {
    std::cout << "No background jobs to list.\n";
  }

}

void Quash::KillJobPid(std::string pid) {
  std::string cmd[2] = {"kill", pid};
  Run(cmd, false, 2);
}

void Quash::KillJob(std::string jobid) {
  std::string cmd[2] = {"kill", ('%' + jobid)};
  Run(cmd, false, 2);
}
