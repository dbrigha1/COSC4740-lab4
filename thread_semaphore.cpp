#include <cstdio> //needed for perror, and printf
#include <pthread.h>
#include <cstdlib> //needed for rand(), srand(), and exit() 
#include <unistd.h> //needed for sleep()
#include "semp.h"

/*
    Follow the directions in the comments and the assignment.  Start by reading
    the application() and main() functions.

    Remember that when the program finishes, it should always report
    5 available resources!  Any more or less, then something isn't right!

    Try it out before making any changes:
    
    g++ thread_semaphore.cpp -lpthread
    ./a.out

    Run a.out several times and you should see the results of the race condition!

*/

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
Semaphore s;
/*
    DECLARE SEMAPHORES GLOBALLY SO THEY ARE SHARED BY ALL THREADS
    using the semp.h implementation, semaphores can be declared as
                      Semaphore s;

    In main, you should initialize the semaphores using
                    semaphore_init(&s, value);
    where value is the value you want to initialize the semaphore to
    i.e. 1 for a mutex style semaphore
  
    The two operations provided from semp.h are
                    semaphore_down( &s );
    which is the wait() and decrements the semaphore, and then
                    semaphore_up( &s );
    which is the signal() and increments the semaphore
*/


int decrease_count(int count)
{
    if(available_resources < count)
    {        
        return -1;
    }
    else
    {
        available_resources -= count;
        return 0;       
    }
}

int increase_count(int count)
{
    available_resources += count;
    return 0;
}

/*
    For part 2, implement the increase and decrease
    using a binary semaphore!
*/
void decrease_S(int count)
{
    //Don't forget to keep track of available_resources
    //so we can see that it is working correctly
    //Also, don't forget to avoid race conditions on available_resources
}

void increase_S(int count)
{
    //Don't forget to keep track of available_resources
    //so we can see that it is working correctly
    //Also, don't forget to avoid race conditions on available_resources
}

//An "applicaion" function that threads will run
void* application(void * id)
{
    int myID = *((int*) id);
    
    //Start a random number of application instances (between 1 and 3)
    int c = ((int) rand() % 3)+1;

    /*
        Part 1:
        Identify the race conditions involved in the following lines of 
        code (including the decrease_count and increase_count functions above.)

        Use a binary semaphore (mutex lock) to modify decrease_count and increase_count
        to prevent the race conditon.
    */
    //Need to get the correct number of resources (licenses)    
    //Each application instance needs to request these resources
    //and continues to do so until they get them.
    //NOTE: this is busy waiting!  Can a counting semaphore be used
    //      instdead to avoid busy waiting?
    //      Part 2 explores this option!
    

    while( decrease_count( c ) == -1 );    
    
    printf("Application %d is starting %d instances.\n", myID, c);
    //Use the application for a while
    sleep( rand() % 2);
    //Release the resource
    increase_count( c );
    
    /*
        End Part 1
    */

    /*
        Part 2
        Write the implementation for decrease_S(int count)
        and increase_S(int count) using a counting semaphore.
        Then comment out the code for part one, uncomment the follow code,
        and run it.  You should not deadlock or have race conditions!
        (Hint, you will need to use the mutex lock from part 1 as well
            to do this correctly!)
    */
    /*   
    decrease_S(c);
    printf("Application %d is starting %d instances.\n", myID, c);
    //Use the application for a while
    sleep( rand() % 2);
    //Release the resource
    increase_S( c );
    */
    /*
        End Part 2
    */
}


int main(int argc, char** argv)
{
    //Declare the worker threads
    pthread_t applications[10];
    int app_ids[10];    
    //seed the random number generator
    srand((unsigned)time(0));
    /*
        initilize the semaphore for Part 1
        (the mutex/binary semaphore)
    */
        
    /*
        initilize the semaphore for Part 2
        (the counting semaphore)
    */
    
    //create the "applications"
    for(int i = 0; i < 10; i++)
    {
        //assing the application id
        app_ids[i] = i;
        //Create an application worker thread
        if (pthread_create(&applications[i], NULL, application, &app_ids[i])) 
        {
            perror("error creating the first thread");
            exit(1);
        }
    }
    //wait for threads to finish
    for(int i = 0; i < 10; i++)
    {
        pthread_join(applications[i], 0);
    }
    printf("Final Available Resources: %d\n", available_resources);
}
