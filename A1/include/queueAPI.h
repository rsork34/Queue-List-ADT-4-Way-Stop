/**
 * @file queueAPI.h
 * @author Ryan Sorkin
 * @date May 2018
 * @brief File containing the function definitions of a queue
 */

#ifndef QUEUE_API
#define QUEUE_API

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

/**
 *A struct for the Queue ADT
 **/
typedef struct Queue
{
  /** A List to be stored inside the queue **/
   List * theList;

  /** First node in the queue **/
  Node * front;

  /** Last node in the queue **/
  Node * back;

  /** length of the queue **/
  int length;
}Queue;

/** Function to allocate memory and return a queue ADT that will
*   encapsulate a list ADT
*@return pointer to the Queue which has memory allocated to it
*@param list struct that has the contents of the queue
**/
Queue * create(List * list);

/** Function to destroy and free all memory allocated for the Queue
*@param queue ADT with memory allocated to it
**/
void destroy(Queue * queue);

/** Function to add a pointer to any data to the queue
*   Adds data to the end of the queue
*@param queue ADT with memory allocated to it
*@param data to a void pointer to data that is non NULL
**/
void add(Queue * queue, void * data);

/** Removes the front item in the Queue and returns it
*@param queue ADT with memory allocated to it
*@return A void pointer to data from the front of the queue
**/
void * dequeue(Queue * queue);

/** A function to determine the number of items in a queue
*@param queue ADT with memory allocated to it
*@return Length of the queue as an int
**/
int length(Queue * queue);

/** Function to determine if the queue is empty or not
*   Returns 1 if list is null or empty, 0 otherwise
*@param queue ADT with memory allocated to it
*@return An int to represent true or false
**/
int isEmpty(Queue * queue);

#endif
