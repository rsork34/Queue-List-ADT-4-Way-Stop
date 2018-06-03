/**
 * @file sorkinRyanA1Libray.h
 * @author Ryan Sorkin
 * @date May 2018
 * @brief File containing the functions to be used in assignment 1
   that are not to be used in either list or queue ADT. Also includes
   car struct.
 */

#ifndef A1_LIBRARY_H
#define A1_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "queueAPI.h"

/** Car struct that is meant to go inside the queue for the
    assignment simulation **/
typedef struct car{
    char comingFrom[2]; // Direction car is coming from (N, E, S, W)
    char direction[2]; // Direction car is going (F, R, L)
    float arrivalTime; // Time the car arrived in the queue
    float waitTime;
    float travelTime; // Time it takes for car to travel
} Car;

/** Once a car is passed in its information is printed
*@param a void pointer to data, expected to be a Car *
**/
void printCarData(void * data);

/** Compare the arrival time of two cars, return:
*   0 if they arrived at the same time
*   1 if car 1 arrived first
*   -1 if car 1 arrived second
*@oaran void pointer to first car to be compared
*@param void pointer to second car to be compared
**/
int compareCars(const void * first, const void * second);

/** Free the memory associated with a car
*@param void pointer to car to be freed
**/
void deleteCar(void * data);

/** Create and return a car based on info read from file
*@param pointer to line read in from file
*@return a pointer to allocated memory to a Car struct
**/
Car *makeCar(char * data);

/** Determines if the next car in the queue is ready
*   to cross the intersection, depends on current time
*@param Queue for the north lane
*@param Queue for the east lane
*@param Queue for the south lane
*@param Queue for the west lane
*@param the current simulation time
*@return a pointer to the car whos turn it is
**/
Node *getTurn(Queue * northQueue, Queue * eastQueue, Queue * southQueue, Queue * westQueue, float counter);

/** "Move" the car across the intersection and increase the simulation
*   timer depending on the direction the car went
*@param Queue for the north lane
*@param Queue for the east lane
*@param Queue for the south lane
*@param Queue for the west lane
*@param A pointer to the node of the current car going
*@param a pointer to the simulation timer
**/
void moveCar(Queue * northQueue, Queue * eastQueue, Queue * southQueue, Queue * westQueue, Node * node, float * counter);

/** Keeps track of total wait time per lane and cars traveled per lane
*@param The current car that is going across the intersection
*@param 2D array to keep track of total travel time, cars traveled per lane
*@param simulation timer, to calculate wait time
**/
void waitPerLane(Node * node, float lanes[2][4], float counter);

/** Display stats regarding the simulation:
*   Total time, longest wait, ave wait, ave wait per lane
*@param 2D array to keep track of total travel time, cars traveled per lane
*@param current simulation time
*@param longest wait time
*@param number of cars that have travelled through the simulation
**/
void printStats(float lanes[2][4], float counter, float maxWait, int carCounter);

void updateWaitTime(Queue * toUpdate, float counter, float travelTime);


#endif
