// #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include <stdlib.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

void fun() {
      time_t s;
     time_t e;
  
    time(&s);

    pid_t pid=fork();
    if (pid==0) { /* child process */
        static char *argv[]={"-hda","kernel.iso",NULL};
        execv("/opt/homebrew/bin/qemu-system-i386",argv);

        // exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
        time(&e);

    double time_taken = ((double)(e-s)); // in seconds
        printf("fun() took %f seconds to execute \n", time_taken);

    }
}
int main() {
    //fun();
    for (int i =0; i< 120; i++) {
        int val = sin(2.0 * 3.14159265358979323846264338327950 * 440.0 / (double) 48000 * i) * 10000;
        printf("%d, ",val );
    }
   
 // Calculate the time taken by fun()
 
   

return 0;
}


