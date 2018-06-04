/**
 * @file sorkinRyanLab1.c
 * @author Ryan Sorkin
 * @date May 2018
 * @brief File containing functions for linked list ADT
 */

#include "LinkedListAPI.h"

List *initializeList(
    void (*printFunction)(void *toBePrinted),
    void (*deleteFunction)(void *toBeDeleted),
    int (*compareFunction)(const void *first,const void *second))
{
  // Make and allocate memory for list pointer
  List * listPtr;
  listPtr = malloc(sizeof(List));

  // Set head and tail to NULL
  listPtr->head = NULL;
  listPtr->tail = NULL;

  // Set delete, print, compare to function pointers passed in
  listPtr->printData = printFunction;
  listPtr->deleteData = deleteFunction;
  listPtr->compare = compareFunction;

  return listPtr;
}

Node *initializeNode(void *data)
{
  // Create and allocate memory for a Node pointer
  Node * nodePtr = malloc(sizeof(Node));

  // Set data to parameter, next and previous to NULL
  nodePtr->data = data;
  nodePtr->next = NULL;
  nodePtr->previous = NULL;

  return nodePtr;
}

void insertFront(List *list, void *toBeAdded)
{
  // List is NULL, return
  if (list == NULL)
  {
    return;
  }

  // List is empty, set toBeAdded to head
  if (list->head == NULL)
  {
    list->head = (Node*)toBeAdded;
    list->tail = (Node*)toBeAdded;
    return;
  }

  // Add new Node to front of list
  Node * newHead = (Node*)toBeAdded;
  newHead->next = list->head;
  list->head->previous = newHead;
  list->head = newHead;
}

void insertBack(List *list, void *toBeAdded)
{
  // The list is NULL, return
  if (list == NULL)
  {
    return;
  }

  // The list is empty, set toBeAdded to the head
  if (list->head == NULL)
  {
    insertFront(list, toBeAdded);
    return;
  }

  // Insert Node at end of List
  // Create temp Node and traverse list to last Node
  Node * curNode = list->head;
  while (curNode->next != NULL)
  {
    curNode = curNode->next;
  }

  // Create new node and insert at end
  Node * newTail = (Node*)toBeAdded;
  curNode->next = newTail;
  newTail->previous = curNode;
  list->tail = newTail;
}

void deleteList(List *list)
{
  // List is null, return
  if (list == NULL)
  {
    return;
  }

  // Free and delete every node then free the list

  while (list->head)
  {
    Node * temp = list->head;
    list->head = list->head->next;

    list->deleteData((void*)temp);
  }
  free(list);
}

void insertSorted(List *list, void *toBeAdded)
{
  // List or data are NULL, return
  if (list == NULL || toBeAdded == NULL)
  {
    return;
  }

  // List is empty, insert node at head
  // or toBeAdded is greater than head, insert as new head
  if (list->head == NULL || list->compare((void*)list->head, toBeAdded) < 0)
  {
    insertFront(list, toBeAdded);
    return;
  }
  // Only one node in list, insert at end of list
  else if (list->head->next == NULL)
  {
    insertBack(list, toBeAdded);
    return;
  }

  // Temp pointer to keep track of current node in list
  Node * curNode = list->head;

  // Loop while the next node > toBeAdded to find correct spot
  while (list->compare((void*)curNode->next, toBeAdded) > 0)
  {
    curNode = curNode->next;

    // If the end of the list is reached add node to end and return
    if (curNode->next == NULL)
    {
      insertBack(list, toBeAdded);
      return;
    }
  }

  // Add the new Node to the correct position and return
  Node * newNode = (Node*)toBeAdded;
  newNode->next = curNode->next;
  newNode->previous = curNode;
  newNode->next->previous = newNode;
  curNode->next = newNode;
  return;
}

int deleteDataFromList(List *list, void *toBeDeleted)
{
  // Failure if  list is null or empty
  if (list == NULL || list->head == NULL)
  {
    return EXIT_FAILURE;
  }

  // Temp node to keep track of current node
  Node * temp = list->head;



  // Iterate until the end of the list
  while (temp)
  {
    // Node to be deleted is found
    if (list->compare((void*)temp, toBeDeleted) == 0)
    {
      // If the Node to be deleted is the head of the list
      if (temp == list->head)
      {
        // Delete the node
        list->head = temp->next;

        // If the new head is not NULL set previous to NULL
        if (list->head)
        {
          list->head->previous = NULL;
        }
      }
      // Node to be deleted is the tail of the list
      else if (temp == list->tail)
      {
        if (temp->previous)
        {
          temp->previous->next = NULL;

          // Delete the node
        }
      }
      // Node to be deleted is in the middle
      else
      {
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
      }
      list->deleteData((Node*)temp);

      return EXIT_SUCCESS;
    }

    temp = temp->next;
  }

  // Node was not found, return -1
  return -1;
}

void *getFromFront(List *list)
{
  // Return NULL if list is NULL or empty
  if (list == NULL || list->head == NULL)
  {
    return NULL;
  }

  return list->head;
}

void *getFromBack(List *list)
{
  // Return NULL if list is NULL or empty
  if (list == NULL || list->head == NULL)
  {
    return NULL;
  }

  return list->tail;
}

void printForward(List *list)
{
  // Return if list is NULL or empty
  if (list == NULL || list->head == NULL)
  {
    return;
  }

  Node * curNode = list->head;
  while (curNode)
  {
    list->printData(curNode);
    curNode = curNode->next;
  }
}

void printBackwards(List *list)
{
  // Return if list is NULL or empty
  if (list == NULL || list->head == NULL)
  {
    return;
  }

  Node * curNode = list->tail;
  while (curNode)
  {
    list->printData(curNode);
    curNode = curNode->previous;
  }
}

int getLength(List * list)
{
  // If the list is empty return 0
  if (list == NULL || list->head == NULL)
  {
    return 0;
  }

  // Initialize length to 0 and start a temp node from
  // front of the list
  int length = 0;
  Node * temp = list->head;

  // Add to counter for every Node in the list
  while (temp)
  {
    length++;
    temp = temp->next;
  }

  return length;
}
