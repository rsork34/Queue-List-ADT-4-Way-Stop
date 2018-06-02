/**
 * @file sorkinRyanA1.c
 * @author Ryan Sorkin
 * @date May 2018
 * @brief Assignment 1 for CIS*2520 of a 4 way stop
   utilizing Linked List and Queue ADTs.
 */

#include "LinkedListAPI.h"
#include "queueAPI.h"

Queue * create(List * list)
{
  // Allocate memory for a new Queue struct and initialize variables
  Queue * newQueue = malloc(sizeof(Queue));
  newQueue->theList = list;
  newQueue->front = list->head;
  newQueue->back = list->tail;
  newQueue->length = getLength(list);

  // Return created Queue
  return newQueue;
}

void destroy(Queue * queue)
{
  // If the queue is already NULL return
  if (queue == NULL)
  {
    return;
  }

  // Delete the list in the queue, destroy pointers, and free Queue
  deleteList(queue->theList);
  queue->front = NULL;
  queue->back = NULL;
  free(queue);
}

void add(Queue * queue, void * data)
{
  // If the queue or data given is NULL return
  if (queue == NULL || data == NULL)
  {
    return;
  }

  // Add data to back of queue and update queue length
  insertBack(queue->theList, data);
  queue->back = data;
  queue->length++;
}

void * dequeue(Queue * queue)
{
  // If the list is NULL or empty return NULL
  if (queue == NULL || queue->front == NULL)
  {
    return NULL;
  }

  // Find first Node in list and remove it, update Queue
  void * toRemove = getFromFront(queue->theList);
  deleteDataFromList(queue->theList, toRemove);
  queue->front = getFromFront(queue->theList);
  queue->length--;

  return toRemove;
}

int length(Queue * queue)
{
  // If the queue is NULL or empty return 0
  if(queue == NULL || queue->front == NULL)
  {
    return 0;
  }

  // Return the length of the list inside the Queue
  return getLength(queue->theList);
}

int isEmpty(Queue * queue)
{
  // Return 1 if list is NULL or empty
  if (queue == NULL || queue->front == NULL)
  {
    return 1;
  }

  return 0;
}
