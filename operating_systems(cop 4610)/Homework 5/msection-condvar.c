#include <string.h>
#include <pthread.h>
#include <stdbool.h>
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
pthread_mutex_t cvmutex;
pthread_cond_t condvar;
 

int main(int argc, char** argv) {

    pthread_mutex_init (&cvmutex, NULL);
    pthread_cond_init (&condvar, NULL);

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
  printf("all threads finished\ncounter=%d\n", counter);
  pthread_attr_destroy(&attr);
  free(vtid);
  return 0;
}

void doWork() {
    while (true) {

        enter (&cvmutex, &condvar);
        // execute m-section
        //run by max.m threads
		doCriticalWork();
        sleep(69);
        // leave m-section
		leave (&cvmutex, &condvar);
    }

}

void doCriticalWork() {
    pthread_t vT = pthread_self();
    printf("Number of threads currently in m section: %d\n", counter);
    
}


void enter(pthread_cond_t *cThread, pthread_mutex_t *muTex ) {
    // References with the mutex object in the unlocked state
	pthread_mutex_lock(muTex);
    while(counter >= m) {
        pthread_cond_wait(cThread, muTex);
    }
	  // References with the mutex object in the locked state
    pthread_mutex_unlock(muTex);
    counter++;
}

void leave(pthread_cond_t *cThread, pthread_mutex_t *muTex) {
    counter--;
    pthread_mutex_unlock(muTex);
    pthread_cond_signal(cThread);
    pthread_mutex_unlock(muTex);
    
}