#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <string>

#include "Quash.h"

class Executive {
  public:
    Executive(char **envp);
    void Run();

  private:
    std::string* path;
    std::string home;

};

#endif
