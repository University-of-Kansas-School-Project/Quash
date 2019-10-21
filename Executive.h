#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <string>

#include "Quash.h"

struct Process;

class Executive {
  public:
    Executive(char **envp);
    void Run();

  private:
    Quash* prog;
};

#endif
