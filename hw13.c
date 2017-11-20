#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int READ = 0;
  int WRITE = 1;
  int f;
  int fds_p_to_c[2]; //contains descriptors for each end of the pipe
  //int fds_c_to_p[2];

  pipe(fds_p_to_c);
  //pipe(fds_c_to_p);

  f = fork();

  if(f){ //parent
    close(fds_p_to_c[READ]); //close parent's ability to read
    int i = 101;
    printf("parent about to write to child... \n");
    sleep(2);
    write(fds_p_to_c[WRITE], &i, sizeof(i)); //writes to the other end of the pipe
    printf("parent written to child: %d \n", i);
  }else{ //child
    close(fds_p_to_c[WRITE]);
    int i;
    read(fds_p_to_c[READ], &i, sizeof(i));
    printf("child read: %d \n", i);
  }

  return 0;
}
