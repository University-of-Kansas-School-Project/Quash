#ifndef SQUASH_H
#define SQUASH_H

#include <iostream>
#include <string>

class Squash {
  public:
    //Constructor
    Squash();

    //Member Functions
    bool SetPath(std::string path);
    bool ChangeDir(std::string dir);
    void Exit();
    bool Run(std::string programPath, std::string programArgs);
    void PrintJobs();
    bool WriteOut(std::string path);
    bool ReadIn(std::string path);
    bool Pipe(std::string leftProgram, std::string rightProgram);
  //bool KillJob(int sigNum, int jobID);

  private:
    //Private Member Variables
    std::string path;
    std::string home;
    std::string currentDir;

};
#endif
