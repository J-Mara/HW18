#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1

int main() {
  int fds[2];
  pipe( fds );
  int ret[2];
  pipe(ret);
  int f = fork();
  if(f == 0){
     char name[100];
     printf("Enter your name: ");
     fgets(name, 100, stdin);
     close(fds[READ]);
     close(ret[WRITE]);
     write(fds[WRITE], name, 100);
     char res[100];
     read(ret[READ], res, 100);
     printf("%s\n", res);
  }
  else{
    char data[100];
    close(fds[WRITE]);
    close(ret[READ]);
    read(fds[READ], data, sizeof(data));
    int i = 0;
    while(data[i]){
      data[i] = toupper(data[i]);
      i++;
    }
    write(ret[WRITE], data, 100);
  }
}
