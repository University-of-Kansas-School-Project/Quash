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
  std::string inp = "";
  while(b){
    bool isBG = false;
    bool inPipe = false;
    int cPipe = 0;
    //std::list<int> lPipe;
    int lPipe =0;
    std::cout<<"quash> ";
    //std::getline(std::cin, inp);
    inp = "";
    std::getline(std::cin, inp);
    int countSP=1;
      for(int lcv = 0; lcv < inp.length(); lcv++) {
        inp[lcv] = std::tolower(inp[lcv]);
        if(inp[lcv] == ' ' || inp[lcv] == '\0') {
          countSP++;
        }
      }

    std::istringstream inpA;
    inpA.str(inp);
    std::string inpArgs[countSP+1];
    int ind = 0;

    for(int i =0; i<countSP; i++){
      inpA >> inpArgs[i];
      if(inpArgs[i] == "|"){
        inPipe = true;
        cPipe ++;
        lPipe = i;
      //  lPipe.push_back(i);
      }
    }

      if(inp[inp.size()-1] == '&')
        isBG = true;
      //user defined path
          //std::cout<<" Inp Args: "<<inpArgs[0];
          // for(int i =0; i<countSP; i++)
          //   std::cout<<" Args: "<<inpArgs[i]


    //non user defined path

    std::cout<<std::endl;
    //  std::cout << inp <<std::endl;
      if(inp == "quit" || inp == "exit") {
        std::cout <<"Goodbye!\n";
        exit(0);
      }
      else if(inPipe && cPipe > 0){
        std::string leftP[lPipe];
        std::string rightP[countSP-lPipe];
        //std::cout<<lPipe<<std::endl;
        //std::cout<<countSP - lPipe-1<<std::endl;
        for(int i =0; i<lPipe; i++){
          leftP[i] = inpArgs[i];
          //std::cout<<leftP[i]<<" ";
        }
        std::cout<<std::endl;
        for(int i = 0; i<countSP-lPipe; i++){
          rightP[i] = inpArgs[i+lPipe+1];
          //std::cout<<rightP[i]<<" ";
        }
        //std::cout<<std::endl;
        prog->Pipe(leftP, rightP);
        inPipe = false;
      }
      else
        prog->Run(inpArgs, isBG, countSP);
    }
}
