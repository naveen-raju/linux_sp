#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_CMD 16
#define SHELL "sh"

int main(int argc, char *argv[]) 
{
   pid_t child_pid;
   int   status, quit = 0;
   char  cmd[MAX_CMD], param[MAX_CMD];

   printf("$mini_shell$: usage : <command> <param>\n");
   while (1) {
      printf("$mini_shell$");
      scanf("%s", cmd);
      if (strcmp(cmd, "quit") == 0) {
         break;
      }
      scanf("%s", param);

      switch ((child_pid = fork())) {
         case -1:
            printf("failed to fork a child\n");
            break;;

         case 0:
            //child process
            if (execlp(cmd, cmd, param, (char *)0) == -1) {
                  printf("failed to perform exec, %s\n", strerror(errno));
                  exit(1);
            }
            exit(0);

         default:
            if (wait(&status) == -1) {
               printf("error during waiting for the child , %s\n", strerror(errno));
            }
            break;
      }
   }
   return 0;
}
