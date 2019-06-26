#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

class Shell {
public:
  bool runCommand(char *const command[]);
  std::string readAvail();
  size_t write(std::string str);
  void setBlocking(bool b = false);

private:
  int fd[2];
};

#endif // SHELL_H
