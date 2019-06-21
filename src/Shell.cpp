#include "Shell.hpp"

int setNonblocking(int fd, bool shouldBlock = false) {
  int flags = !shouldBlock;
  return ioctl(fd, FIONBIO, &flags);
}

void Shell::setBlocking(bool b) {
  setNonblocking(fd[1], b);
}

bool Shell::runCommand(char *const command[]) {
  pid_t apid = getpid();
  int *pid   = &apid;

  pipe(fd);
  auto infd = &fd[0], outfd = &fd[1];

  int p1[2], p2[2];

  if(!pid || !infd || !outfd)
    return false;

  if(pipe(p1) == -1)
    goto err_pipe1;
  if(pipe(p2) == -1)
    goto err_pipe2;
  if((*pid = fork()) == -1)
    goto err_fork;

  if(*pid) {
    /* Parent process. */
    *infd  = p1[1];
    *outfd = p2[0];
    close(p1[0]);
    close(p2[1]);
    setNonblocking(fd[1]);
    return true;
  } else {
    /* Child process. */
    dup2(p1[0], STDIN_FILENO);
    dup2(p2[1], STDOUT_FILENO);
    dup2(p2[1], STDERR_FILENO);
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
    execvp(*command, command);
    /* Error occured. */
    fprintf(stderr, "error running %s: %s", *command, strerror(errno));
    abort();
  }

err_fork:
  close(p2[1]);
  close(p2[0]);
err_pipe2:
  close(p1[1]);
  close(p1[0]);
err_pipe1:
  return false;
}

std::string Shell::readAvail() {
  std::string availData;
  bool dataInPipe = true;
  char buf[1024];
  size_t count = 1024;
  do {
    ssize_t r = read(fd[1], buf, count);
    if(r == -1 && errno == EAGAIN) {
      // no data yet
      dataInPipe = false;
    } else if(r > 0) {
      // received data
      availData.append(buf, r);
    } else {
      dataInPipe = false;
      return availData;
    }
    return availData;
  } while(dataInPipe);
}

void Shell::write(std::string str) {
  size_t written = ::write(fd[0], str.c_str(), str.size());
}
