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

  unsigned long niceIncr;
  unsigned long iChild;

  ErrCode err;
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message
  }
  else{

    niceIncr = strtoul(argv[3], NULL, 10);
    //niceIncr = argc-3;

    printf (" PID of initial process : %d\n", ( int) getpid () ) ;
    printf (" PPID of initial process : %d ( the shell I was started from ?)\n",
    (int) getppid () ) ;

     for(iChild=0;iChild < niceIncr; iChild++){

           int forkRetVal = fork ();
           unsigned long iChilds = iChild*niceIncr;

           switch(forkRetVal) {
              case -1:  // ... failed
              perror("Fork failed .\n");
              exit(1);
    
              case 0:  // First child process:
              printf (" Child : My PID = %d\n", (int) getpid () ) ;
              printf (" Child : My parent ’s PID = %d\n", (int) getppid () ) ;
              printf("IChilds is: %ld\n", iChilds);
              break;

              default: //parent
              printf(" Parent : My PID = %d\n", ( int) getpid () ) ;
              printf(" Parent : My child ’s PID = %d\n", forkRetVal ) ;
              break;
    
          }
      }
  }
  printf("\n");  // Newline at end
  printf("niceinc: %ld\n", niceIncr);
  printf("\n");  // Newline at end

  return 0;
}
