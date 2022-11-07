/******************************************************************************
 * File:         display.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: syntax check
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "displayFunctions.h"

char **global_argv;

int main(int argc, char *argv[]) {
  global_argv = argv;

  int niceIncr;
  int iChild;

  unsigned long int numOfTimes;
  char printMethod, printChar;
  ErrCode err;
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) 
    DisplayError(err);        // Print an error message
 
    printMethod = argv[1][0];
    numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
    printChar = argv[3][0];
    niceIncr = (int) strtoul(argv[3], NULL, 10);

    printf (" PID of initial process : %d\n", ( int) getpid () ) ;
    printf (" PPID of initial process : %d ( the shell I was started from ?)\n",
    (int) getppid () ) ;

      int forkRetVal = fork () ;

     for(iChild=0;iChild <= niceIncr; iChild++){
           switch(forkRetVal) {
              case -1:  // ... failed
              perror("Fork failed .\n");
              exit(1);
    
              case 0:  // First child process:
              printf (" Child : My PID = %d\n", ( int) getpid () ) ;
              printf (" Child : My parent ’s PID = %d\n", ( int) getppid () ) ;
              break;

              default: //parent
              printf(" Parent : My PID = %d\n", ( int) getpid () ) ;
              printf(" Parent : My child ’s PID = %d\n", forkRetVal ) ;
              break;
    
          }
      }
  
  printf("\n");  // Newline at end
  printf("niceinc: %d\n", niceIncr);
  printf("\n");  // Newline at end

  return 0;
}
