#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int READ = 0;
  int WRITE = 1;
  int f;
  int fds_p_to_c[2]; //contains descriptors for each end of the pipe
  int fds_c_to_p[2];

  pipe(fds_p_to_c);
  pipe(fds_c_to_p);

  f = fork();

  if(f){ //parent
    close(fds_p_to_c[READ]); //close parent's ability to read
    int i = 101;
    printf("parent about to write to child... \n");
    //sleep(2);
    write(fds_p_to_c[WRITE], &i, sizeof(i)); //writes to the other end of the pipe
    printf("parent written to child: %d \n", i);

    close(fds_c_to_p[WRITE]); //close parent's ability to write with this pipe
    read(fds_c_to_p[READ], &i, sizeof(i)); //waiting for input
    printf("parent read: %d \n", i);
    
  }else{ //child
    close(fds_p_to_c[WRITE]);
    int i;
    read(fds_p_to_c[READ], &i, sizeof(i)); //waiting for input
    printf("child read: %d \n", i);

    i *= 2; //child performs arithmetic operation of choice (*2)
    printf("child multiplying number by 2: %d \n", i);

    close(fds_c_to_p[READ]);
    printf("child about to write to parent... \n");
    sleep(2);
    write(fds_c_to_p[WRITE], &i, sizeof(i)); //sending new value to parent
    printf("child  written to parent: %d \n", i);
  }

  return 0;
}
