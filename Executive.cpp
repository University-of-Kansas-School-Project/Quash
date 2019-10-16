#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Executive.h"
#include "Quash.h"


Executive::Executive(char **envp) {
  std::string unparsedPath = "";
  std::string* path;
  std::string home;
  std::string pwd;

  for(int lcv=0;envp[lcv] != nullptr; lcv++) {
    // std::cout << envp[lcv] <<std::endl;
    std::string envVar = envp[lcv];
      if(envVar.substr(0,5) == "PATH=") {
        unparsedPath = envVar.substr(5, envVar.size());
      }
      else if(envVar.substr(0,5) == "HOME=") {
        home = envVar.substr(5, envVar.size());
      }
      else if(envVar.substr(0,4) == "PWD=") {
        pwd = envVar.substr(4, envVar.size());
      }
  }

  std::istringstream ps(unparsedPath);
  std::string p;
  int countP=1;
  for(int lcv=0; lcv < unparsedPath.size(); lcv++ ) {
    if(unparsedPath[lcv] == ':') {
      countP++;
    }
  }
  path = new std::string[countP];
  int ind = 0;

  while(std::getline(ps, p, ':')) {
      path[ind] = p;
      ind ++;
  }
  prog = new Quash(path, home, pwd);
}


void Executive::Run() {
  bool b = true;
  bool isBG = false;
  std::string inp = "";
  while(b){
  std::cout<<"quash> ";
  //std::getline(std::cin, inp);
  std::getline(std::cin, inp);

  for(int lcv = 0; lcv < inp.size(); lcv++) {
    inp[lcv] = std::tolower(inp[lcv]);
  }

  int countSP=1;
  for(int lcv=0; lcv < inp.size(); lcv++ ) {
    if(inp[lcv] == ' ') {
      countSP++;
    }
  }

  std::istringstream inpA(inp);
  std::string inpArgs[countSP];
  int ind = 0;

while(!inpA.eof()){
  inpA >> inpArgs[ind];
  ind ++;
}

  if(inp[inp.size()-1] == '&')
    isBG = true;
  //user defined path
  if(inp[0] == '/') {
    if(ind > 1)
      prog->Run(inpArgs[0], isBG, inpArgs);
    else
      prog->Run(inpArgs[0], isBG);
  }


  //non user defined path

  std::cout<<std::endl;
  //  std::cout << inp <<std::endl;
    if(inp == "quit" || inp == "exit") {
      std::cout <<"Goodbye!\n";
      b = false;
    }
  }
}
