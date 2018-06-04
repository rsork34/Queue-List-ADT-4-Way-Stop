/**
 * @file sorkinRyanA1Libray.h
 * @author Ryan Sorkin
 * @date June 2018
 * @brief File containing the functions to be used in assignment 1
   that are not to be used in either list or queue ADT. Also includes
   car struct.
 **/

#ifndef A1_LIBRARY_H
#define A1_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "queueAPI.h"

/**
*   Car struct that is meant to go inside the queue for the
*   assignment simulation
**/
typedef struct car{
    /** Direction car is coming from (N, E, S, W) **/
    char comingFrom[2];/** Direction car is coming from (N, E, S, W) **/
    char direction[2]; /** Direction car is going (F, R, L) **/
    float arrivalTime; /** Time the car arrived in the queue **/
    float waitTime; /** How long the car is waiting at the front of its line **/
    float travelTime; /** Time it takes for car to travel **/
} Car;

/** Once a car is passed in its information is printed
*@param data to a void pointer, expected to be a Car *
**/
void printCarData(void * data);

/** Compare the arrival time of two cars, return:
*   0 if they arrived at the same time
*   1 if car 1 arrived first
*   -1 if car 1 arrived second
*@param first void pointer to first car to be compared
*@param second void pointer to second car to be compared
**/
int compareCars(const void * first, const void * second);

/** Free the memory associated with a car
*@param data to a  void pointer to Car* to be freed
**/
void deleteCar(void * data);

/** Create and return a car based on info read from file
*@param data pointer to string read in from file
*@return a pointer to allocated memory to a Car struct
**/
Car *makeCar(char * data);

/** Determines if the next car in the queue is ready
*   to cross the intersection, depends on current time
*@param northQueue the queue of cars coming from North
*@param eastQueue the queue of cars coming from East
*@param southQueue the queue of cars coming from South
*@param westQueue the queue of cars coming from West
*@param counter is the current simulation time
*@return a pointer to the car whos turn it is
**/
Node *getTurn(Queue * northQueue, Queue * eastQueue, Queue * southQueue, Queue * westQueue, float counter);

/** "Move" the car across the intersection and increase the simulation
*   timer depending on the direction the car went
*@param northQueue the queue of cars coming from North
*@param eastQueue the queue of cars coming from East
*@param southQueue the queue of cars coming from South
*@param westQueue the queue of cars coming from West
*@param node that holds the current car going
*@param counter pointer of the simulation timer
**/
void moveCar(Queue * northQueue, Queue * eastQueue, Queue * southQueue, Queue * westQueue, Node * node, float * counter);

/** Keeps track of total wait time per lane and cars traveled per lane
*@param node that stores the current car that is going across the intersection
*@param lanes that stores a 2D array to keep track of total travel time, cars traveled per lane
*@param counter to a simulation timer, to calculate wait time
**/
void waitPerLane(Node * node, float lanes[2][4], float counter);

/** Display stats regarding the simulation:
*   Total time, longest wait, ave wait, ave wait per lane
*@param lanes that stores a 2D array to keep track of total travel time, cars traveled per lane
*@param counter to the simulation time
*@param maxWait is the longest wait time so far
*@param carCounter is the number of cars that have travelled through the simulation
**/
void printStats(float lanes[2][4], float counter, float maxWait, int carCounter);

/** Updates the time that those at the front of each lane have
*   waited for their turn
*@param toUpdate is the Queue that needs to be updated
*@param counter to the simulation time
*@param travelTime how long the car going across the intersection takes to travel
**/
void updateWaitTime(Queue * toUpdate, float counter, float travelTime);

#endif
