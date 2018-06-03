/**
 * @file sorkinRyanA1Libray.c
 * @author Ryan Sorkin
 * @date May 2018
 * @brief Functions to be used in sorkinRyanA1.c utilizing the
   queue and list ADTs
 */

#include "LinkedListAPI.h"
#include "queueAPI.h"
#include "sorkinRyanA1Libray.h"
#include <string.h>

void printCarData(void * data)
{
  // Get the current car to print from Node passed in
  Node * temp = (Node*)data;
  Car * toPrint = (Car*)temp->data;

  // Display where they're coming from, going, time they arrived
  printf("%s ", toPrint->comingFrom);
  printf("%s ", toPrint->direction);
  printf("%.0f\n", toPrint->arrivalTime);
}

int compareCars(const void * first, const void * second)
{
  Node * node1 = (Node*)first;
  Node * node2 = (Node*)second;

  Car * car1 = (Car*)node1->data;
  Car * car2 = (Car*)node2->data;

  int num1 = car1->arrivalTime;
  int num2 = car2->arrivalTime;

  // Cars arrived at the same time
  if (num1 == num2)
  {
    return 0;
  }
  // Car 1 arrived first
  else if (num1 < num2)
  {
    return 1;
  }
  // Car 1 arrived second
  else
  {
    return -1;
  }
}

void deleteCar(void * data)
{
  if (data == NULL)
  {
    return;
  }

  // Delete and free node
  Node * temp = (Node*)data;
  temp->next = NULL;
  temp->previous = NULL;
  free(temp->data);
  free(temp);
}

Car *makeCar(char * data)
{
  // Ensure data passed in is valid
  if (data == NULL || strcmp(data, "\n") == 0)
  {
    return NULL;
  }

  // Get first token from data
  char * tok = strtok(data, " ");

  // If no tokens were found return NULL
  if (tok == NULL || strcmp(tok, "\n") == 0)
  {
    return NULL;
  }

  // Create a car and set direction it is coming from
  Car * newCar = malloc(sizeof(struct car));
  newCar->comingFrom[0] = tok[0];
  newCar->comingFrom[1] = '\0';

  // Get the next token and check that info is still valid
  // If no tokens were found return NULL
  tok = strtok(NULL, " ");
  if (tok == NULL || strcmp(tok, "\n") == 0)
  {
    free(newCar);
    return NULL;
  }

  // Set direction car is going
  newCar->direction[0] = tok[0];
  newCar->direction[1] = '\0';

  // Get the next token and check that info is still valid
  // If no tokens were found return NULL
  tok = strtok(NULL, " ");
  if (tok == NULL || strcmp(tok, "\n") == 0)
  {
    free(newCar);
    return NULL;
  }

  // Set the time that the car arrived  in the queue
  newCar->arrivalTime = atoi(tok);

  // Determine and set time to travel for the car
  if (strcmp(newCar->direction, "F") == 0)
  {
    newCar->travelTime = 2.0;
  }
  else if (strcmp(newCar->direction, "R") == 0)
  {
    newCar->travelTime = 1.5;
  }
  else if (strcmp(newCar->direction, "L") == 0)
  {
    newCar->travelTime = 3.5;
  }
  else
  {
    free(newCar);
    return NULL;
  }

  newCar->waitTime = 0;
  return newCar;
}

Node *getTurn(Queue * northQueue, Queue * eastQueue, Queue * southQueue, Queue * westQueue, float counter)
{
  Node * nodeN = (Node*)northQueue->theList->head;
  Node * nodeE = (Node*)eastQueue->theList->head;
  Node * nodeS = (Node*)southQueue->theList->head;
  Node * nodeW = (Node*)westQueue->theList->head;

  // If there are 4 cars in the intersection going at once
  // North goes
  if (nodeN && nodeE && nodeS && nodeW)
  {
    Car * carN = (Car*)nodeN->data;
    Car * carE = (Car*)nodeE->data;
    Car * carS = (Car*)nodeS->data;
    Car * carW = (Car*)nodeW->data;

    // All 4 cars arrived at the same time and can currently go
    if (carN->waitTime == carE->waitTime &&
        carE->waitTime == carS->waitTime &&
        carS->waitTime == carW->waitTime &&
        carN->arrivalTime <= counter)
    {
      return nodeN;
    }
  }

  /* Cases for 3 cars arriving at the same time */
  // North, East, and South, North goes
  if (nodeN && nodeE && nodeS)
  {
    Car * carN = (Car*)nodeN->data;
    Car * carE = (Car*)nodeE->data;
    Car * carS = (Car*)nodeS->data;

    if (carN->waitTime == carE->waitTime &&
        carE->waitTime == carS->waitTime &&
        carN->arrivalTime <= counter)
    {
      return nodeN;
    }
  }

  // North, East, and West, West goes
  if (nodeN && nodeE && nodeW)
  {
    Car * carN = (Car*)nodeN->data;
    Car * carE = (Car*)nodeE->data;
    Car * carW = (Car*)nodeW->data;

    if (carN->waitTime == carE->waitTime &&
        carE->waitTime == carW->waitTime &&
        carN->arrivalTime <= counter)
    {
      return nodeW;
    }
  }

  // North, South, and West, South goes
  if (nodeN && nodeS && nodeW)
  {
    Car * carN = (Car*)nodeN->data;
    Car * carS = (Car*)nodeS->data;
    Car * carW = (Car*)nodeW->data;

    if (carN->waitTime == carS->waitTime &&
        carS->waitTime == carW->waitTime &&
        carN->arrivalTime <= counter)
    {
      return nodeS;
    }
  }

  // East, South, and West, East goes
  if (nodeE && nodeS && nodeW)
  {
    Car * carE = (Car*)nodeE->data;
    Car * carS = (Car*)nodeS->data;
    Car * carW = (Car*)nodeW->data;

    if (carE->waitTime == carS->waitTime &&
        carS->waitTime == carW->waitTime &&
        carE->arrivalTime <= counter)
    {
      return nodeE;
    }
  }

  /* For if 2 cars arrive at the same time */
  // North, South
  if (nodeN && nodeS)
  {
    Car * carN = (Car*)nodeN->data;
    Car * carS = (Car*)nodeS->data;

    if (carN->waitTime == carS->waitTime &&
        carN->arrivalTime <= counter)
    {
      // If both cars are going straight, North car goes first
      if (carN->direction[0] == 'F' && carS->direction[0] == 'F')
      {
        return nodeN;
      }
      // North going straight, South turning, North goes
      else if (carN->direction[0] == 'F' && carS->direction[0] != 'F')
      {
        return nodeN;
      }
      // South going straight, North turning, South goes
      else if (carS->direction[0] == 'F' && carN->direction[0] != 'F')
      {
        return nodeS;
      }
    }
  }

  // East, West
  if (nodeE && nodeW)
  {
    Car * carE = (Car*)nodeE->data;
    Car * carW = (Car*)nodeW->data;

    if (carE->waitTime == carW->waitTime &&
        carE->arrivalTime <= counter)
    {
      // If both cars are going straight, East car goes first
      if (carE->direction[0] == 'F' && carW->direction[0] == 'F')
      {
        return nodeE;
      }
      // East going straight, West turning, East goes
      else if (carE->direction[0] == 'F' && carW->direction[0] != 'F')
      {
        return nodeE;
      }
      // West going straight, East turning, West goes
      else if (carW->direction[0] == 'F' && carE->direction[0] != 'F')
      {
        return nodeW;
      }
    }
  }

  // North and East, North goes
  if (nodeN && nodeE)
  {
    Car * carN = (Car*)nodeN->data;
    Car * carE = (Car*)nodeE->data;

    if (carN->waitTime == carE->waitTime &&
        carN->arrivalTime <= counter)
    {
      return nodeN;
    }
  }

  // North and West, West goes
  if (nodeN && nodeW)
  {
    Car * carN = (Car*)nodeN->data;
    Car * carW = (Car*)nodeW->data;

    if (carN->waitTime == carW->waitTime &&
        carN->arrivalTime <= counter)
    {
      return nodeW;
    }
  }

  // East and South, East goes
  if (nodeE && nodeS)
  {
    Car * carE = (Car*)nodeE->data;
    Car * carS = (Car*)nodeS->data;

    if (carE->waitTime == carS->waitTime &&
        carE->arrivalTime <= counter)
    {
      return nodeE;
    }
  }

  // South and West, South goes
  if (nodeS && nodeW)
  {
    Car * carS = (Car*)nodeS->data;
    Car * carW = (Car*)nodeW->data;

    if (carS->waitTime == carW->waitTime &&
        carS->arrivalTime <= counter)
    {
      return nodeS;
    }
  }

  // If there is at least 1 car waiting to go
  if (nodeN || nodeE || nodeS || nodeW)
  {
    float maxWait = 0;
    char going;

    /* Determine which car has been waiting longest */
    if (nodeN)
    {
      Car * carN = (Car*)nodeN->data;

      if (maxWait < carN->waitTime)
      {
        maxWait = carN->waitTime;
        going = 'N';
      }
    }
    if (nodeE)
    {
      Car * carE = (Car*)nodeE->data;

      if (maxWait < carE->waitTime)
      {
        maxWait = carE->waitTime;
        going = 'E';
      }
    }
    if (nodeS)
    {
      Car * carS = (Car*)nodeS->data;

      if (maxWait < carS->waitTime)
      {
        maxWait = carS->waitTime;
        going = 'S';
      }
    }
    if (nodeW)
    {
      Car * carW = (Car*)nodeW->data;

      if (maxWait < carW->waitTime)
      {
        maxWait = carW->waitTime;
        going = 'W';
      }
    }

    if (going == 'N')
    {
      return nodeN;
    }
    else if (going == 'E')
    {
      return nodeE;
    }
    else if (going == 'S')
    {
      return nodeS;
    }
    else if (going == 'W')
    {
      return nodeW;
    }

  }

  // No car is ready to travel
  return NULL;
}

void moveCar(Node * node, float * counter)
{
  // Current car
  Car * car = (Car*)node->data;

  // Increase the counter depending on the direction they go
  *counter += car->travelTime;

  // If the next car is coming from the same direction
  // Add a second to the time for it to move up
  if (node->next)
  {
    // Next car in queue
    Node * nextNode = (Node*)node->next;
    Car * nextCar = (Car*)nextNode->data;

    // If it is from the same direction add a second
    if (car->comingFrom[0] == nextCar->comingFrom[0])
    {
      *counter += 1.0;
    }
  }
}

void waitPerLane(Node * node, float lanes[2][4], float counter)
{
  // Current car that is travelling
  Car * car = (Car*)node->data;

  // Car comes from either N E S or W
  if (car->comingFrom[0] == 'N')
  {
    lanes[0][0] += counter - car->arrivalTime;
    lanes[1][0] += 1.0;
  }
  else if (car->comingFrom[0] == 'E')
  {
    lanes[0][1] += counter - car->arrivalTime;
    lanes[1][1] += 1.0;
  }
  else if (car->comingFrom[0] == 'S')
  {
    lanes[0][2] += counter - car->arrivalTime;
    lanes[1][2] += 1.0;
  }
  else if (car->comingFrom[0] == 'W')
  {
    lanes[0][3] += counter - car->arrivalTime;
    lanes[1][3] += 1.0;
  }
}

void printStats(float lanes[2][4], float counter, float maxWait, int carCounter)
{
  // Total time waited, to calculate average wait time
  float totalWaited = 0;

  printf("\n***************************************\n");
  printf("*                STATS                *\n");
  printf("***************************************\n");

  printf("Total simulation time: %.2f seconds\n", counter);
  printf("Longest wait time %.2f seconds\n", maxWait);

  // Calculate and display total average wait time
  for (int i = 0; i < 4; i++)
  {
    totalWaited += lanes[0][i];
  }
  printf("Average wait time: %.2f seconds\n", totalWaited / carCounter);

  // Wait time for north lane
  if (lanes[1][0] == 0) // Total wait time was 0
  {
    printf("Average wait time NORTH lane: 0 seconds\n");
  }
  else // Calculate and display North lane wait time
  {
    printf("Average wait time NORTH lane: %.2f seconds\n", (lanes[0][0] / lanes[1][0]));
  }

  // Wait time for east lane
  if (lanes[1][1] == 0) // Total wait time was 0
  {
    printf("Average wait time EAST  lane: 0 seconds\n");
  }
  else // Calculate and display East lane wait time
  {
    printf("Average wait time EAST  lane: %.2f seconds\n", (lanes[0][1] / lanes[1][1]));
  }

  // Wait time south lane
  if (lanes[1][2] == 0) // Total wait time was 0
  {
    printf("Average wait time SOUTH lane: 0 seconds\n");
  }
  else // Calculate and display South lane wait time
  {
    printf("Average wait time SOUTH lane: %.2f seconds\n", (lanes[0][2] / lanes[1][2]));
  }

  // Wait time west lane
  if (lanes[1][3] == 0) // Total wait time was 0
  {
    printf("Average wait time WEST  lane: 0 seconds\n");
  }
  else // Calculate and display West lane wait time
  {
    printf("Average wait time WEST  lane: %.2f seconds\n", (lanes[0][3] / lanes[1][3]));
  }
}
