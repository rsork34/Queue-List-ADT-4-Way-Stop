/**
 * @file testMain.c
 * @author Ryan Sorkin
 * @date June 2018
 * @brief A main to test out the functions made for a Queue ADT
 * that encapsulates a Linked List ADT
 */

#include "LinkedListAPI.h"
#include "queueAPI.h"
#include "sorkinRyanA1Libray.h"

int main()
{
  // List and Queue ADTs for testing purposes
  List * testList;
  Queue * testQueue;

  // Info to initialize Cars
  char info1[6] = "N R 1";
  char info2[6] = "E F 10";
  char info3[6] = "N L 2";
  char info4[6] = "W F 11";
  char info5[6] = "N R 3";
  char info6[6] = "S L 5";

  // Initialize cars
  Car * car1 = makeCar(info1);
  Car * car2 = makeCar(info2);
  Car * car3 = makeCar(info3);
  Car * car4 = makeCar(info4);
  Car * car5 = makeCar(info5);
  Car * car6 = makeCar(info6);

  // Initialize Nodes with cars
  Node * node1 = initializeNode((void*)car1);
  Node * node2 = initializeNode((void*)car2);
  Node * node3 = initializeNode((void*)car3);
  Node * node4 = initializeNode((void*)car4);
  Node * node5 = initializeNode((void*)car5);
  Node * node6 = initializeNode((void*)car6);

  // Initialize linked list
  void (*printFunction)(void * data) = &printCarData;
  void (*deleteFunction)(void *toBeDeleted) = &deleteCar;
  int (*compareFunction)(const void *first,const void *second) = &compareCars;

  testList = initializeList(printFunction, deleteFunction, compareFunction);
  testQueue = create(testList);

  printf("Adding 3 nodes to the queue\n");

  add(testQueue, node1);
  add(testQueue, node2);
  add(testQueue, node3);

  printf("Truth value for queue being empty: %d\n", isEmpty(testQueue));
  printf("The length is: %d\n", length(testQueue));
  printf("Deleting 2 nodes from the queue\n");

  dequeue(testQueue);
  dequeue(testQueue);

  printf("The length is: %d\n", length(testQueue));
  printf("Truth value for queue being empty: %d\n", isEmpty(testQueue));
  printf("Adding 3 nodes to the queue\n");

  add(testQueue, node4);
  add(testQueue, node5);
  add(testQueue, node6);

  printf("The length is: %d\n", length(testQueue));
  printf("Deleting the queue\n");
  destroy(testQueue);

  printf("The length is: %d\n", length(testQueue));
  printf("Truth value for queue being empty: %d\n", isEmpty(testQueue));
}
