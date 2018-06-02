/**
 * @file sorkinRyanA1.c
 * @author Ryan Sorkin
 * @date May 2018
 * @brief Assignment 1 for CIS*2520 of a 4 way stop
   utilizing Linked List and Queue ADTs.
 */

#include "LinkedListAPI.h"
#include "queueAPI.h"
#include "sorkinRyanA1Libray.h"
#include <string.h>

int main(int argc, char ** argv)
{
  // Buffer for reading in from file and file pointer
  char buffer[50];
  FILE * fp = NULL;

  // List of cars to be read into
  List * carList = NULL;

  // Global time, car counter, and ave wait time
  float counter = 0.0;
  float maxWait = 0.0;
  int carCounter = 0;

  // Wait time and cars traveled for each lane
  // {0, 0, 0, 0} == {N, E, S, W}
  float lanes[2][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}};

  // User does not use two arguments in command line, exit program
  if (argc != 2)
  {
    printf("Missing file name, exiting\n");
    return EXIT_FAILURE;
  }

  // Initialize linked list
  void (*printFunction)(void * data) = &printCarData;
  void (*deleteFunction)(void *toBeDeleted) = &deleteCar;
  int (*compareFunction)(const void *first,const void *second) = &compareCars;
  carList = initializeList(printFunction, deleteFunction, compareFunction);

  // Open file from command line for reading
  fp = fopen(argv[1], "r");

  // Invalid file name, exit program
  if (!fp)
  {
    return EXIT_FAILURE;
  }

  // Read in each line from file to initialize cars in program
  while (fgets(buffer, 50, fp))
  {
    // Create a car with data from file and add it to the list
    Car * newCar =  makeCar(buffer);
    if (newCar) // Ensure a valid car was created
    {
      // Add cars based on arrival time -> earlier is first
      Node * tempNode = initializeNode((void*)newCar);
      insertSorted(carList, tempNode);
    }
  }
  // Close the input file
  fclose(fp);

  // Take list and initialize the queue
  Queue * carQueue = create(carList);

  printf("\nCars gone, in order:\n");

  // Go through each car in the queue
  while(!isEmpty(carQueue))
  {
    // Determine which car is going to turn, if any
    Node * curNode = getTurn(carQueue->theList, counter);

    // A car is ready to go in the queue
    if (curNode)
    {
      Car * curCar = (Car*)curNode->data;

      // Check if car has waited longest, if so update maxWait
      if (counter - curCar->arrivalTime > maxWait)
      {
        maxWait = counter - curCar->arrivalTime;
      }

      // Move the car and print out its details
      printCarData((void*)curNode); // Print data
      waitPerLane(curNode, lanes, counter); // Increase counter for each lane
      moveCar(curNode, &counter); // Increase counter
      dequeue(carQueue); // Remove car from front of queue

      // Increment car counter
      carCounter++;
    }
    // No car went, increase counter
    else
    {
      counter += 0.5;
    }
  }

  // Free the queue
  destroy(carQueue);

  printStats(lanes, counter, maxWait, carCounter);
  return 0;
}
