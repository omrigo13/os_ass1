#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"


int main(int argc, char **argv)
{
  int pid = fork();
  if (pid != 0){
    sleep(1);
    for(int i=0; i<1500; i++)
      fprintf(1, "P");
  }
  else{
    for(int i=0; i<1500; i++)
      fprintf(1, "C");
  }
  exit(0);
}