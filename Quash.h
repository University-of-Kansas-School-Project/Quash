#ifndef QUASH_H
#define QUASH_H

#include <iostream>
#include <string>

class Quash {
  public:
    //Constructor
    Quash(std::string* p, std::string h, std::string pd);

    //Member Functions
    bool ChangeDir(const char* dir);
    bool Run(std::string* programPath, bool isBackgroundProcess, int c);
    void PrintJobs();
    bool WriteOut(std::string path);
    bool ReadIn(std::string path);
    bool Pipe(std::string* leftProgram, std::string* rightProgram);
  //bool KillJob(int sigNum, int jobID);

    //Helper Functions
    std::string* GetPath() { return path; }
    std::string GetHome() { return home; }
    std::string GetPwd() {return pwd; }
    std::string GetPathRaw() {return pathRaw; }

    void SetPath(std::string* pth) { path = pth; }
    void SetHome(std::string h) { home = h; }
    void SetPwd(std::string pd) { pwd = pd; }
    void SetPathRaw(std::string raw) { pathRaw = raw; }

    void Import(std::string inputFile);


  private:
    //Private Member Variables
    std::string* path;
    std::string pathRaw;
    std::string home;
    std::string pwd;

};
#endif
