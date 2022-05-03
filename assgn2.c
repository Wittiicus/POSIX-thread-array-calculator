#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "log.h"

int logindex = 0;
int* logi = &logindex;

void* thread_function (void*);

// mutex for log, required by logging functions for thread-safe code
pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;

// defines a mutex for done
pthread_mutex_t tdone = PTHREAD_MUTEX_INITIALIZER;

// initialize the thread function

// defining a structure to for a personality: index , the thread id
// tid , name of the personality, linecount ,
// and flag indicating when the personality's
// processing is completed.
typedef struct {
  int index;
  pthread_t tid;
  int lineCount;
  int done;
  char name[10];
} PERSON;


PERSON person[8];
// create the struct of personalities

int done = 0;
FILE* flog = NULL;
// a global variable int done=0;
// that serves as the indicator when the processing is done

// FILE* flog = NULL;


// function main --------------------------------------------------------
int main() {
  int i;
  int* value_ptr;

  // check if the make level is between 1 to 8, if not,
  // return 0 and give a warning
  // if there is a correct numbers, print out the persons
  // you can do it by using if to compare _level
  if (_level < 1 || _level > 8) {
    msg("give a waring");
    return 0;
  } else{
    int i = 0;
    for ( i = 0 ; i < _level ; i++) { 
      person[i].index = i; 
      int x = snprintf(person[i].name , 10, "Person%d", i);
      person[i].lineCount = 0 ;
      person[i].tid = -1 ; 
      person[i].done = -1 ; 
  }
    msg("There are %d personalities", _level);
    for (i = 0; i < _level; i++)
    {
      msg("person%d", i);
    }
  }


        
    

  // after checking, create a log file just like what you did in assgn1
  // with create_log()
  create_log("assgn2.log");

  // in here you would add people to the personality table with for loop
  // can give tid and done as -1
  // linecount set as 0
  //loop for i = 0 .. _level-1
    //initialize the values on the table for for Person_i
  //endloop







  //do
    //loop for i = 0 .. _level-1
      //if Person_i not done yet, create a thread for it with pthread_create()
      //include a test if pthread_create() worked, if not,
      //display an error message and terminate the program with exit(1);
    //endloop

    //loop for i = 0 .. _level-1
      //if Person_i not done yet, join the thread with pthread_join()
      //include a test if pthread_join() worked, if not,
      //display an error message and terminate the program with exit(1);
    //endloop

  //while ! done
  //Since done starts with value 0, the testing of its value
  //must be at the bottom of the loop, not at the top of the loop


  do {
      for (i = 0; i < _level; i ++ ) {
          if (person[i].done == 1) continue;
        //if Person_i not done yet, create a thread for it with pthread_create()
          pthread_create( &person[i].tid , NULL,&thread_function , &person[i]); 

        //pthread_create(&tid, NULL, processfd, &fd)
        //The creating process (or thread) must provide a location for storage of the thread id.
        //For now, pass a null pointer to indicate the default attributes.
        //The third parameter is just the name of the function for the thread to run.
        //The last parameter is a pointer to the arguments.

        //if the pthread_create() failed,
        //display an error message and terminate the program with exit(1);
    } 

    for (i = 0; i < _level; i ++) {
      if (person[i].done == 1) continue;
      pthread_join(person[i].tid , (void**)&value_ptr) ; 
 
      // pthread_join(pthread_t thread, void **value_ptr)
      // if fails, display a warning
  }
  }
  while (done != 0);


  for (i = 0; i < _level; i++) {
    msg("Person %s processed %d lines",person[i].name, person[i].lineCount);
  }
  return 0;


// end function main


}
// function conversation ------------------------------------------
// thread functions
void* thread_function(void* arg) {
  void* value_ptr = NULL;
  PERSON *p;
  char line[100]; //the input line
  

  // locks the mutex for done
  pthread_mutex_lock(&tdone);
  p = (PERSON*) arg;
  if (p->done == -1) {
      p->done = 0;
      done++;
  }
  // If the Person is just starting, it increments done by 1

   // Displays the prompt
   msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message: ", getpid, pthread_self(), person->index, person->name);

   // Gets the users response
   fgets(line, 100 , stdin);

   // Unlocks the mutex for done
   pthread_mutex_unlock(&tdone);



   // If the response started with quit, then
      // locks the mutex for the global variable done
      // decrements done by 1
      // unlocks the mutex for done
      // displays and logs a message that the user quit
      // exits the thread, its return value is irrelevant
  char quitStr[] = "quit";

   if (strcmp(line, quitStr) == 10) {
     pthread_mutex_lock(&tdone);
     p->done = 1;
     done = done - 1;
     //do decrements done by 1
     pthread_mutex_unlock(&tdone);
     Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n user quit", getpid,pthread_self(), person->index, person->name, line);
     pthread_exit(&value_ptr);
   } else {
     Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n %s", getpid,pthread_self(),p->index,p->name,line); 
     p->done = 0 ; 
     p->lineCount++ ;
     pthread_exit(&value_ptr);
}







   

}







