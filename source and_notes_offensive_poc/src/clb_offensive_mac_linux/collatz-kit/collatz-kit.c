/*
 * m0nk's general Copywrite: 
 *      For fun: Open Source & Free
 *      For profit: pay me 
 * m0nk's extended Copywrite:
 *      For better human good: Open Source & Free
 *      For evil or nefarious use: Pay me
 *
 *
 * Just some notes:
 *
 * m0nk -> This simple program is designed to drop the CollaztKit thread
 *          onto an Android system and just let it run. Dirty, no cleanup
 *          and simple as hell. < enjoy />
 *
 * m0nk -> TODO:
 *      Add the shim code (maybe)
 *      Add the % util code
 *      Add some sort of backdoor status checking (maybe)
 *
 *
 * More on the algorithm here:
 *      Blah Blah
 *
 * More on the underlying math here: 
 *      Blah Blah
 */


//#include <linux/kernel.h>
//#include <linux/kthread.h>      // for threads
//#include <linux/sched.h>        // for task_struct
//#include <linux/time.h>         // for using jiffies  
//#include <linux/timer.h>
//#include <linux/random.h>
//#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

//static struct task_struct *collatz_kit;


long collatz_sequence_processor( long seed ) {  
    long new_seed = 0;
    long collatz_sequence_length = 0;
    
    new_seed = seed;    

    printf("Staged value of the current collatz sequence: %ld", new_seed);
        
    while ( new_seed > 1 ){
        //printk(KERN_INFO "Staged value of the current collatz sequence: %ld", new_seed);
           
        if( (new_seed % 2) != 0 ){
            new_seed = ((3 * new_seed) + 1);
            collatz_sequence_length++;
        } else {
            new_seed = (new_seed / 2);
            collatz_sequence_length++;
        }
        printf("%ld -> ", new_seed);
    }
    printf("\n");

    return collatz_sequence_length;
}

int collazt_kit_main_thread( void ) {

    unsigned long rand_seed_value = 0;
    unsigned long temp_length_couter = 0;
    
    //printk(KERN_INFO "In collatz_kit");
    printf( "In collatz_kit");
    
    //srand (time(NULL));            // initialize random seed is a horrible way....
    srand (666);                     // initialize random seed is a worse way....
    
    while ( (1+1) != 666 ) {

        rand_seed_value = ( rand() % 5000 ) + 1;
        //rand_seed_value = get_random_int();
        
        temp_length_couter = collatz_sequence_processor( rand_seed_value );
        //temp_length_couter = collatz_sequence_processor( rand_seed_value );
        
        //printk(KERN_INFO "collatz_kit ran with initial value: %ld for %ld", rand_seed_value, temp_length_couter);
        printf("collatz_kit ran with initial value: %ld for %ld", rand_seed_value, temp_length_couter);
    
        temp_length_couter = 0;        
    }

    return 0;
}

int main (void) {
    printf("initializing infection...");

    collazt_kit_main_thread();

    /*
    char  thread_name[11] = "CollatzKit";

    printk(KERN_INFO "initializing infection...");
    
    
    collatz_kit = kthread_create(collazt_kit_main_thread, NULL, thread_name);
    
    if( (collatz_kit) ) {
        //printk(KERN_INFO "spinning up processing now...");
      
        //Here is probably where we want to limit the proccessing scope of this thread.
        wake_up_process(collatz_kit);
    }
    */


    return 0;
}

