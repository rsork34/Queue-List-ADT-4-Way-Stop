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

  // List of cars to be read into for each lane
  List * carListNorth = NULL;
  List * carListEast  = NULL;
  List * carListSouth = NULL;
  List * carListWest  = NULL;

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

  // Initialize a list for each direction
  carListNorth = initializeList(printFunction, deleteFunction, compareFunction);
  carListEast = initializeList(printFunction, deleteFunction, compareFunction);
  carListSouth = initializeList(printFunction, deleteFunction, compareFunction);
  carListWest = initializeList(printFunction, deleteFunction, compareFunction);

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

      // Add car to the list depending on direction it is arriving from
      if (newCar->comingFrom[0] == 'N')
      {
        insertSorted(carListNorth, tempNode);
      }
      else if (newCar->comingFrom[0] == 'E')
      {
        insertSorted(carListEast, tempNode);
      }
      else if (newCar->comingFrom[0] == 'S')
      {
        insertSorted(carListSouth, tempNode);
      }
      else
      {
        insertSorted(carListWest, tempNode);
      }
    }
  }
  // Close the input file
  fclose(fp);

  // Take lists and initialize the queues for each lane
  Queue * carQueueNorth = create(carListNorth);
  Queue * carQueueEast = create(carListEast);
  Queue * carQueueSouth = create(carListSouth);
  Queue * carQueueWest = create(carListWest);

  // Set up an array of the 4 lanes
  Queue * carQueueArray[4];
  carQueueArray[0] = carQueueNorth;
  carQueueArray[1] = carQueueEast;
  carQueueArray[2] = carQueueSouth;
  carQueueArray[3] = carQueueWest;

  printf("\nCars gone, in order:\n");

  // Go through each car in the queue
  while(!isEmpty(carQueueArray[0]) || !isEmpty(carQueueArray[1]) || !isEmpty(carQueueArray[2]) || !isEmpty(carQueueArray[3]))
  {
    // Determine which car is going to turn, if any
    Node * curNode = getTurn(carQueueArray[0], carQueueArray[1], carQueueArray[2], carQueueArray[3], counter);

    // A car is ready to go in the queue
    if (curNode)
    {
      Car * curCar = (Car*)curNode->data;

      // Check if car has waited longest, if so update maxWait
      if (counter - curCar->arrivalTime > maxWait)
      {
        maxWait = counter - curCar->arrivalTime;
      }
      // Move the car, print out its details, update wait time
      // for other cars
      printCarData((void*)curNode); // Print data
      waitPerLane(curNode, lanes, counter); // Increase counter for each lane
      moveCar(carQueueArray[0], carQueueArray[1], carQueueArray[2], carQueueArray[3], curNode, &counter); // Increase counter

      // Remove car from correct queue
      if (curCar->comingFrom[0] == 'N')
      {
        dequeue(carQueueArray[0]);
      }
      else if (curCar->comingFrom[0] == 'E')
      {
        dequeue(carQueueArray[1]);
      }
      else if (curCar->comingFrom[0] == 'S')
      {
        dequeue(carQueueArray[2]);
      }
      else
      {
        dequeue(carQueueArray[3]);
      }

      // Increment car counter
      carCounter++;
    }
    // No car went, increase counter
    else
    {
      counter += 0.5;
    }
  }

  // Free each queue
  destroy(carQueueNorth);
  destroy(carQueueEast);
  destroy(carQueueSouth);
  destroy(carQueueWest);

  printStats(lanes, counter, maxWait, carCounter);

  return 0;
}
