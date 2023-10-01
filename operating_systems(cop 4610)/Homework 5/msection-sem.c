#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
void enter();
void leave();
void doWork();
void doCriticalWork();
 
// amount of threads
int m = 3;
int counter = 0;
// semaphore object
sem_t semObject;
 
int main(int argc, char** argv) {
  sem_init (&semObject, 0, 3);
 
 long i;
 // number of threads
 long n = 10;   
 pthread_attr_t attr;
 pthread_t *vtid = (pthread_t *) calloc(n, sizeof(pthread_t));
 if (vtid == NULL) {
   printf("Error \n\n");
   exit(1);
 }
 
 // initializes the thread attributes object 
 pthread_attr_init(&attr);
 // sets the detach state attribute
 pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  for (i=0; i<n; i++) {
   int r = pthread_create(&vtid[i], &attr, doWork, (void*)i);
   if (r < 0) {             
     printf("Error %d\n", r);
     exit(2);
   }
 }
  for (i=0; i<n; i++) {
   // waits for defined thread to terminate
   pthread_join(vtid[i], NULL);
 }
 // counting for completed threads
 printf("all threads finished\ncounter=%ld\n", counter);
 pthread_attr_destroy(&attr);
 free(vtid);
 return 0;
}
 
void doWork() {
   while (true) {
		
	    // limited access to m threads
       enter (&semObject);
	   // execute m-section
     //run by max.m threads
	   doCriticalWork();
       sleep(69);
     // leave m-section
	   leave (&semObject);
   }
 
}
 
void doCriticalWork() {
   pthread_t vT = pthread_self();
   printf("Number of threads currently in m section: %ld\n", counter);
  
}
 
void enter(sem_t *semObject) {
   sem_wait (semObject);
   counter++;
}
 
void leave(sem_t *semObject) {
   counter--;
   sem_post(semObject);
}