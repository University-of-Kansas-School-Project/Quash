#ifndef QUASH_H
#define QUASH_H

#include <iostream>
#include <string>
#include <list>

//Process Struct
struct Process {
  Process(int p, std::string s, std::string* c, std::string r, int noa) {
    pid = p;
    status = s;
    cmd = c;
    cmdRaw = r;
    numOfArgs = noa;
  }

  int pid;
  int numOfArgs;
  std::string status;
  std::string cmdRaw;
  std::string* cmd;
};

class Quash {
  public:
    //Constructor
    Quash(std::string* p, std::string h, std::string pd);

    //Member Functions
    bool ChangeDir(const char* dir);
    bool Run(std::string* programPath, bool isBackgroundProcess, int c);
    bool WriteOut(std::string path);
    bool ReadIn(std::string path);
    bool Pipe(std::string* leftProgram, std::string* rightProgram);

    void ListJobs();
    void ResumeJob(std::string jobid);
    void KillJobPid(std::string pid);
    void KillJob(std::string jobid);

    //Helper Functions
    std::string* GetPath() { return path; }
    std::string GetHome() { return home; }
    std::string GetPwd() {return pwd; }
    std::string GetPathRaw() {return pathRaw; }

    std::list<Process*>* GetBgProccessList() { return bgJobs; }

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

    std::list<Process*>* bgJobs;

};
#endif
