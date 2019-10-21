#include <iostream>
#include <string>

#include "Executive.h"

int main(int argc, char **argv, char **envp) {


  Executive exec(envp);
  exec.Run();
  return 0;
}
