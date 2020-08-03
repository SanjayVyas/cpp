/*
 * ----------------------------------------------------------------------
 * File:      SingleLinkedList.h
 * Project:   SingleLinkedList
 * Author:    Sanjay Vyas
 * 
 * Description:
 *    Implementation of Single Linked List in C++
 * ----------------------------------------------------------------------
 * Revision History:
 * 2020-Aug-04	[SV]: Created
 * ----------------------------------------------------------------------
 */

#ifndef _SINGLELINKEDLIST_H_
#define _SINGLELINKEDLIST_H_

#include <iostream>
using namespace std;

/**
 * Node class represents a single link in the linked list
 * It contains
 *    - Value
 *    - Pointer to the next node
 */
class Node
{
public:
  int value;
  Node *next;

  // Constructor
  Node(int val)
  {
    value = val;
    next = nullptr;
  }
};

/** 
 * List class holds the head and tail pointers of the list
 */
class List
{
private:
  Node *head;
  Node *tail;

public:
  List()
  {
    head = nullptr;
    tail = nullptr;
  }

  /*
   *---------------------------------------------------------------------
   * List operations
   *  addToBack()     - Add a value at the end of the list
   *  addToFront()    - Add a value at the beginning of the list
   *  printForward()  - Print all values from head to tail
   *---------------------------------------------------------------------
   */

  /**
     * Add a value at the end of the list
     * return value indicates whether the value was added
     */
  bool addToBack(int value)
  {
    // Allocate a new node
    Node *newNode = new Node(value);

    // If we failed to allocate, return false
    if (nullptr == newNode)
      return false;

    // Check if this is the first node
    if (nullptr == head)
    {
      // Make head and tail both point to this newNode
      head = newNode;
      tail = newNode;

      return true;
    }

    // This is not the first node, so add it after tail
    tail->next = newNode;

    // Now newNode is the last node, hence, make it the tail
    tail = newNode;
    return true;
  }

  /**
     * Add a value at the beginning of the list
     * return value indicates whether the value was added 
     */
  bool addToFront(int value)
  {
    // Allocate a new node and return false if new return null
    Node *newNode = new Node(value);
    if (nullptr == newNode)
      return false;

    // If this is the first node, make it head and tail
    if (nullptr == head)
      tail = newNode;
    else
      newNode->next = head;
    head = newNode;
    return true;
  }

  /**
     * Print all values from head to tail
     * return value indicates number of nodes printed
     */
  int printForward()
  {
    int count = 0;

    // Go thru all the nodes from head to tail
    for (Node *current = head; current; current = current->next)
    {
      cout << current->value << endl;
      count++;
    }
    return count;
  }
};

#endif
