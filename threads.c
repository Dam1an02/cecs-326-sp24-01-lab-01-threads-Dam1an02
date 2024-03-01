#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/*
   Damian Osorio 
   027044249
   CECS 326 Sec01

Answer the following questions in a long-form comment at the top of your code:
   1. The pthread spins any other thread that isn't the main, and runs the child function with said thread. This results in printing a message every 3 seconds. 

   2. The child thread prints its periodic messages meanwhile the main thread awaits user input, is because the child is asynchronous. This is determined by the os (chooses what is deemed the best) while the child thread is potentially ran on a different cpu core. This results in it having its own program counter. This means that it is asynchronous. Another way would be the operating system knits the threads through the same core and dedicates each thread their own time, so it becomes pseudosynchronous.

*/


static void *child(void *ignored){
   while(1) {
      sleep(3);
      printf("Child is done sleeping 3 seconds.\n");
   }

   return NULL;
}

int main(int argc, char *argv[]){
   pthread_t child_thread; // ID of Thread
   int code; // Error code
   code = pthread_create(&child_thread, NULL, child, NULL); // Attempt Creation of Thread
   if(code) 
      fprintf(stderr, "pthread_create failed with code %d\n", code);

   // Check to Kill Child Thread
   if (getchar() == '\n') { // \n == user pressed enter
      int error = pthread_cancel(child_thread); // Returns 0 if successful
      if (error)
         puts("Failure in cancelling the thread.");
      else
         puts("The child thread has been killed");
   }

   // Validate that main is still alive
   sleep(5);
   printf("Parent is done sleeping 5 seconds.\n");

   return 0;
}