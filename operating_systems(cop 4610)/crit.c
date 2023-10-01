#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h> 

void enter();
void leave();
void doWork(); 
void doCriticalWork(); 

sem_t semaphore; // defining semaphore object
int counter = 0;
int m = 3; // number of maximum threads

int main(int argc, char** argv) {
  
  
  long i;
  long n = 10;    // number of threads
  pthread_attr_t attr;
  pthread_t *vtid = (pthread_t *) calloc(n, sizeof(pthread_t));
  if (vtid == NULL) {
    printf("ERROR: calloc failed\n\n");
    exit(1);
  }
    
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  
  for (i=0; i<n; i++) {
    int r = pthread_create(&vtid[i], &attr, doWork, (void*)i);
    if (r < 0) {              
      printf("ERROR: pthread_create() returned %d\n", r);
      exit(2);
    }
  }
  // now wait for the threads to complete:
  for (i=0; i<n; i++) {
    pthread_join(vtid[i], NULL);
  }
  printf("all threads finished\ncounter=%ld\n", counter);
  pthread_attr_destroy(&attr);
  free(vtid);
  return 0;
}


void doCriticalWork() {
    printf("Thread id: , number of threads in m-section: ");
}

void doWork(int m_threads) {
    while(true) {
       
    }
    return;
}
```