#include "kernel_interface.h"

#include <unistd.h>
#include <iostream>
#include <string.h>
#include <pwd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>


#define ROOT_NAME "root"

#define WRITE_END 1
#define READ_END 0

// Dynamically Load kmod: https://stackoverflow.com/questions/5947286/how-can-linux-kernel-modules-be-loaded-from-c-code

void signal_register(int a, void (*v)(int)){
  signal(a, v);
}

void root_mode(char *argv[], const char * password){
  auto current_name = getpwuid(getuid()); // Gets user info
  bool match = true;
  for(unsigned i = 0; i < sizeof(ROOT_NAME) / sizeof(char); i++){
    if(current_name->pw_name[i] != ROOT_NAME[i]){ // Sometimes the name value is filled with null characters, so we only check a few
      match = false;
    }
  }
  if(match) return; // We don't want to infinitely loop once we are root.
  int     fd[2];
  pid_t   pid;
  pipe(fd); // Pipes output for fork
  pid = fork(); // Splits into two processes
  
  int status;
  if(pid==0){ // If child
    close(fd[1]); // Not writing
    dup2(fd[0], STDIN_FILENO); // Bind read to stdin
    close(fd[0]); // Stop reading
    status = execlp("sudo", "sudo", "-n", "-u", ROOT_NAME, "--stdin", argv[0], (char*) NULL); // Sudo up
    std::cout << strerror(errno) << std::endl; // If we get here, execlp failed
    exit(status); // Exit critically
  } else {
    close(fd[0]); // Not reading
    write(fd[1], password, (strlen(password)+1)); // Send password over pipe
    close(fd[1]); // Stop writing
  }
  waitpid(0, &status, 0); // Wait for child process to end (end of program).
  std::cout << status << std::endl;
  exit(status);
}