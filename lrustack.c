/**
 * @author ECE 3058 TAs
 */

#include <stdlib.h>
#include "lrustack.h"

/**
 * This file contains some starter code to get you started on your LRU implementation. 
 * You are free to implement it however you see fit. You can design it to emulate how this
 * would be implemented in hardware, or design a purely software stack. 
 * 
 * We have broken down the LRU stack's
 * job/interface into two parts:
 *  - get LRU: gets the current index of the LRU block
 *  - set MRU: sets a certain block's index as the MRU. 
 * If you implement it using these suggestions, you will be able to test your LRU implementation
 * using lrustacktest.c
 * 
 * NOTES: 
 *      - You are not required to use this LRU interface. Feel free to design it from scratch if 
 *      that is better for you.
 *      - This will not behave like your traditional LIFO stack  
 */

/**
 * Function to initialize an LRU stack for a cache set with a given <size>. This function
 * creates the LRU stack. 
 * 
 * @param size is the size of the LRU stack to initialize. 
 * @return the dynamically allocated stack. 
 */
lru_stack_t* init_lru_stack(int size) {

    if (size <= 0) {
        return NULL;
    } // if
    //  Use malloc to dynamically allocate a lru_stack_t
	lru_stack_t* stack = (lru_stack_t*) malloc(sizeof(lru_stack_t));
    if (!stack) {
        return NULL;
    } // if
    //  Set the stack size the caller passed in
	stack->size = size;
    
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write any other code needed to initialize your LRU Stack. 
    //  Essentially write any initializations needed for anything you
    //  added to lru_stack_t.
    ////////////////////////////////////////////////////////////////////

    // hint: use malloc to dynamically allocate an array of ints
    // stack -> array = ( data type? ) malloc (? * sizeof(int));

    // hint: iterate through the array and initialize
    // for (int i = 0; i < size; i++) {
    //    stack -> array[i] = ?;
    //}

    stack->array = (int*)malloc(size * sizeof(int));
    if (!stack->array) {
        free(stack);
        return NULL;
    } // if
    for (int i = 0; i < size; i++) {
        stack->array[i] = i;
    } // for

    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////

	return stack;
} // init_lru_stack

/**
 * Function to get the index of the least recently used cache block, as indicated by <stack>.
 * This operation should not change/mutate your LRU stack. 
 * 
 * @param stack is the stack to run the operation on.
 * @return the index of the LRU cache block.
 */
int lru_stack_get_lru(lru_stack_t* stack) {
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write code to get the index of the LRU block from the LRU 
    //  Stack. 
    ////////////////////////////////////////////////////////////////////
    
    // hint: instead of returning 0, return the first element of the array
    // return (stack -> array[?]);
    if (!stack) {
        return -1;
    } // if
    if (!stack->array) {
        return -1;
    } // if
    if ((stack->size) <= 0) {
        return -1;
    } // if

    return stack->array[0];

    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////
} // lru_stack_get_lru

/**
 * Function to mark the cache block with index <n> as MRU in <stack>. This operation should
 * change/mutate the LRU stack.
 * 
 * @param stack is the stack to run the operation on.
 * @param n the index to promote to MRU.  
 */
void lru_stack_set_mru(lru_stack_t* stack, int n) {
	////////////////////////////////////////////////////////////////////
    //  TODO: Write code to set the passed in block index  as the MRU 
    //  element in the LRU Stack. 
    ////////////////////////////////////////////////////////////////////
    
    if (!stack) {
        return;
    } // if
    if (n < 0) {
        return;
    } // if
    if (n >= (stack->size)) {
        return;
    } // if

    // locate entry in array
    int pos = -1;
    for (int i = 0; i < (stack->size); i++) {
        if (stack->array[i] == n) {
            pos = i;
            break;
        } // if
    } // for
    if (pos == -1) {
        return; // Invalid index
    } // if

    // shift elements
    for (int i = pos; i < ((stack->size) - 1); i++) {
        stack->array[i] = stack->array[i + 1];
    } // for
    // move to end of array
    stack->array[(stack->size) - 1] = n;

    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////
} // lru_stack_set_mru

/**
 * Function to free up any memory you dynamically allocated for <stack>
 * 
 * @param stack the stack to free
 */
void lru_stack_cleanup(lru_stack_t* stack) {
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write any code if you need to do additional heap allocation
    //  cleanup
    ////////////////////////////////////////////////////////////////////

    // hint: first free your array
    // free(stack -> ?);
    free(stack->array);
    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////

    free(stack);        // Free the stack struct we malloc'd
} // lru_stack_cleanup