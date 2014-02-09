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


#include <stdio.h>
#include <stdlib.h>

//static struct task_struct *collatz_kit;


long collatz_sequence_processor( long seed ) {  
    long new_seed = 0;
    long collatz_sequence_length = 0;
    
    new_seed = seed;    

    //m0nk: killing the screen prints for greater speeds
    //printf("Staged value of the current collatz sequence: %ld", new_seed);
        
    while ( new_seed > 1 ){

        if( (new_seed % 2) != 0 ){
            new_seed = ((3 * new_seed) + 1);
            collatz_sequence_length++;
        } else {
            new_seed = (new_seed / 2);
            collatz_sequence_length++;
        }
        //m0nk: killing the screen prints for greater speeds
        //printf("%ld -> ", new_seed);
    }
    //m0nk: killing the screen prints for greater speeds
    //printf("\n");

    return collatz_sequence_length;
}

int collazt_kit_main_thread( void ) {
    //m0nk: Commenting out the temp_length_couter when we don't want to print...
     
    unsigned long rand_seed_value = 0;
    //unsigned long temp_length_couter = 0;
    
    //m0nk: killing the screen prints for greater speeds
    //printf( "In collatz_kit");
    
    srand (666);                     // initialize random seed in a horrible way....
    
    while ( (1+1) != 666 ) {

        rand_seed_value = ( rand() % 5000 ) + 1;
        
        //temp_length_couter = collatz_sequence_processor( rand_seed_value );
        collatz_sequence_processor( rand_seed_value );
        
        //m0nk: killing the screen prints for greater speeds
        //printf("collatz_kit ran with initial value: %ld for %ld", rand_seed_value, temp_length_couter);
    
        //temp_length_couter = 0;        
    }

    return 0;
}

int main (void) {
    printf("initializing infection...");

    collazt_kit_main_thread();

    return 0;
}

