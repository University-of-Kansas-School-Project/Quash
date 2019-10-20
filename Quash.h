#ifndef QUASH_H
#define QUASH_H

#include <iostream>
#include <string>

class Quash {
  public:
    //Constructor
    Quash(std::string* p, std::string h, std::string pd);

    //Member Functions
    bool SetPath(std::string path);
    bool ChangeDir(std::string dir);
    bool Run(std::string* programPath, bool isBackgroundProcess, int c);
    void PrintJobs();
    bool WriteOut(std::string path);
    bool ReadIn(std::string path);
    bool Pipe(std::string leftProgram, std::string rightProgram);
  //bool KillJob(int sigNum, int jobID);

  private:
    //Private Member Variables
    std::string* path;
    std::string home;
    std::string pwd;

};
#endif
