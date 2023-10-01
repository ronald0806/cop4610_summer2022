#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> 
 
void thread();
void *thread_fun(void *param);
pthread_mutex_t cvmutex;
pthread_cond_t condvar;
 
class Barrier {
   public:
 
   int counter;
   // number of threads
   Barrier(int n)
   {
       pthread_mutex_init (&cvmutex, NULL);
       pthread_cond_init(&condvar, NULL);
       counter = 0;
   }
 
void wait() {
 
   
   if(counter < 0) {
       pthread_mutex_lock(&cvmutex);
       counter++;
       pthread_cond_wait(&condvar, &cvmutex);
       pthread_mutex_unlock(&cvmutex);
   }
   
   else{
       pthread_mutex_lock(&cvmutex);
       pthread_cond_broadcast(&condvar);
       counter = 0;
       pthread_mutex_unlock(&cvmutex);
   }
 
   };
 
private:
 
int x;
pthread_mutex_t cvmutex;
pthread_cond_t condvar;
 
};
 
// Barrier object declared as a global variable
Barrier shield(7);
 
int main(int argc, char** argv) {
 
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
   int r = pthread_create(&vtid[i], &attr, thread_fun, (void*)i);
   if (r < 0) {             
     printf("Error %d\n", r);
     exit(2);
   }
 }
  // waits for defined thread to terminate
  for (i=0; i<n; i++) {
   pthread_join(vtid[i], NULL);
 }
 // counting for completed threads
 printf("all threads finished\ncounter=%d\n", shield.counter);
 pthread_attr_destroy(&attr);
 free(vtid);
 return 0;
}
 // child threads run this thread function
void *thread_fun(void *param){
   // thread runs in loop
   while(true){
     // work is done
	   shield.wait();
       thread();
   }
}
 
void thread(){
  pthread_t results = pthread_self();
   
   int adding = 0;
   int bundle = 1;
 
   while(adding <= 10) {

       printf("Threads printed: %d\n", bundle);
       printf("Thread identification number: %d\n", thread);
       sleep(69);
       adding++;
       bundle++;
         
   }
    
}