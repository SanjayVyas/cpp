/*-----------------------------------------------------------------------------*
 * Project:   OptimizedAVLTree
 * File:      AVLTree.h
 * Author:    Sanjay Vyas 
 * 
 * Description:
 *    Highly optimized version of AVL,
 *    which does not use recursive method to compute height or balance.
 * 
 *    It tracks the balance as we add or remove node from the tree
 *    the balance field is updated in addNode and removeNode
 * 
 *    rebalance method checks the balance field in node and calls on of the 
 *    four rotation methods, which also resets the balance after rotation.
 * 
 * Revision History:
 *    2018-May-23: Initial Creation
 * 
 * Disclaimer:
 *    This code may contain intentional and unintentional bugs
 *    There are no warranties of the code working correctly
 *----------------------------------------------------------------------------*/

#include <iostream> // Required for cout
#include <iomanip>  // Required for setw
using namespace std;

/**
 * AVL Tree class
 * which is a self balancing tree and achieves O(log n) operation
 * 
 * It contains the following methods
 * 
 *  Regular BST methods
 *      addNode             - Add a new node and reblance if necessary
 *      add                 - Data abstractor wrapper for addNode
 *      removeNode          - Remove a node and rebalance if necessary
 *      remove              - Data abstractor wrapper for removeNode
 *      inorderAscending    - Print the tree in ascending order
 *      printAscending      - Data abstractor method for inorder
 *      inorderDebug        - Print the tree in tree form
 *      printDebug          - Data abstractor method of inorderDebug
 * 
 *  AVL specific methods
 *      rebalance   - rotate the subtree when its off balance
 *      rotateLL    - rotate the subtree left once
 *      rotateRL    - rotate the subtree right once and then left
 *      rotateRR    - rotate the subtree right once
 *      rotateLR    - rotate the subtree left once and then right
 * 
 */
class Tree
{
  /**
   * struct Node is inner to List as only List class needs it
   */
  struct Node
  {
    // If using an earlier version of C++ compiler
    // Move the initialization of left and right into constructor
    Node *left = nullptr;
    int value;
    Node *right = nullptr;

    // balance of the Node
    int balance = 0;

    Node(int val)
    {
      value = val;
    }
  };

private:
  Node *root = nullptr;

  /**
    * All the AVL methods are listed below
    * 
    * AVL is based on rotation - RR, RL, LR, LL
    * Each node has a balance, which is
    *   +1 if the right subtree is deeper than left by 1 level
    *   -1 if the left subtree is deeper than right by 1 level
    *   0  if both left and right have the same depth
    * 
    *    if the balance becomes greater than 1 (+2 or -2)
    *    that part of the tree needs to be rebalanced
    *    which can be done by rotation methods
    * 
    * AVL methods:
    *    rotateRR      - rotate the tree right (RR)
    *    rotateRL      - rotate the tree right first and then left (RL)
    *    rotateLl      - rotate the tree left (LL)
    *    rotateLR      - rotate the tree left first and then right (LR)
    *    rebalance     - check if tree needs rotation and call methods
    *
    *  The following methods are not required in optimized AVL Tree
    *    computeHeight     - Find out height of subtree
    *    computeBalance    - Find out difference of left & right subtree height
    * 
    * BST methods to be modified
    *    addNode requires rebalance after adding the node
    *    removeNode requires rebalance after removing the node
    */

  /**
    * rebalance checks the balance of the current node
    * if its +2 or -2, it calls one of the 4 rebalance nodes
    */
  Node *rebalance(Node *current)
  {
    // We have reached a null node, no balancing required
    if (nullptr == current)
      return nullptr;

    // Right heavy tree
    if (current->balance == +2)
    {
      if (current->right->balance >= 0)
        // If child is heavy to the right, rotateLeft
        current = rotateLL(current);
      else
        // If child is heavy to the left, rotateRightLeft
        current = rotateRL(current);
    }
    // Left heavy tree
    else if (current->balance == -2)
    {
      if (current->left->balance <= 0)
        // If child is heavy to the left, rotateRight
        current = rotateRR(current);
      else
        // If child is heavy to the right, rotateLeftRights
        current = rotateLR(current);
    }

    return current;
  }

  /**
    * Four rotation methods of AVL
    * rotateRR, rotateRL, rotateLR, rotateLL
    */

  Node *rotateLL(Node *current)
  {
    // Point to the child node
    Node *child = current->right;

    // Hand over any left of child to right of current
    current->right = child->left;

    // Now move current to the left of child
    child->left = current;

    // Recalculate balances
    child->balance = child->balance - 1;
    current->balance = -child->balance;

    // Child becomes the parent
    return child;
  }

  Node *rotateRL(Node *current)
  {
    // Point to the child and grandchild nodes
    Node *child = current->right;
    Node *grandchild = child->left;

    // Hand over left and right of grandchild
    child->left = grandchild->right;
    current->right = grandchild->left;

    // current and child become left and right of granchild
    grandchild->left = current;
    grandchild->right = child;

    // Set the new balances
    current->balance = -min(grandchild->balance, 0);
    child->balance = -max(grandchild->balance, 0);
    grandchild->balance = 0;

    // Grandchild becomes the parent
    return grandchild;
  }

  Node *rotateRR(Node *current)
  {
    // Point to the child node
    Node *child = current->left;

    // Hand over child's right to current's left
    current->left = child->right;

    // Now current will become child's right
    child->right = current;

    // Set all balances
    child->balance = child->balance + 1;
    current->balance = -child->balance;

    // Child becomes the parent
    return child;
  }

  Node *rotateLR(Node *current)
  {
    // Point to child and grandchild
    Node *child = current->left;
    Node *grandchild = child->right;

    // Hand over left and right of grandchild
    child->right = grandchild->left;
    current->left = grandchild->right;

    // Now grandchild will point to current and child
    grandchild->left = child;
    grandchild->right = current;

    // Reset child balance
    current->balance = -max(grandchild->balance, 0);
    child->balance = -min(grandchild->balance, 0);
    grandchild->balance = 0;

    // Grandchild becomes the parent
    return grandchild;
  }

  /**
    * To make sure we dont expose internal data like Node *root to caller
    * We will define two methods for each operation
    * private method which will receive and return root
    * public method which will act as Data Abstractor
    */
private:
  // Internal method for adding a node, which uses Node *root
  Node *addNode(Node *current, int valToAdd, bool &heightIncreased)
  {
    // If we have reached null node, create a new node and return it
    // It will not be connected here, but at the previous level
    if (nullptr == current)
    {
      heightIncreased = true;
      return new Node(valToAdd);
    }

    // If we haven't reached null, go down the tree
    // and connect the returned pointer to either left of right
    if (valToAdd > current->value)
    {
      current->right = addNode(current->right, valToAdd, heightIncreased);
      if (heightIncreased)
        current->balance++;
    }
    else if (valToAdd < current->value)
    {
      current->left = addNode(current->left, valToAdd, heightIncreased);
      if (heightIncreased)
        current->balance--;
    }

    // AVL: Change required for AVL balanced tree
    current = rebalance(current);

    // If the balance has become 0, we have rebalanced the subtree
    if (0 == current->balance)
      heightIncreased = false;

    return current;
  }

public:
  // Data abstraction method for adding a node
  void add(int valToAdd)
  {
    // Call the private method and pass root
    bool heightIncreased = false;
    root = addNode(root, valToAdd, heightIncreased);
  }

private:
  // Internal method for removing a node
  Node *removeNode(Node *current, int valToRemove, bool &heightDecreased)
  {
    int priorBalance = 0;

    // If we have reached null node, it means it was not found
    if (nullptr == current)
    {
      heightDecreased = false;
      return nullptr;
    }

    // Now search the value down the tree
    if (valToRemove > current->value)
    {
      current->right = removeNode(current->right, valToRemove, heightDecreased);
      if (heightDecreased == true)
      {
        current->balance--;

        // If previous balance was +1 or -1, it had one child
        // Now if it is 0, both children removed, hence height decreased
        // If its not 0, means one child removed, other exists
        // Hence, height has not yet decreased
        if (current->balance != 0)
          heightDecreased = false;
      }
    }
    else if (valToRemove < current->value)
    {
      current->left = removeNode(current->left, valToRemove, heightDecreased);
      if (heightDecreased == true)
      {
        current->balance++;

        // If previous balance was +1 or -1, it had one child
        // Now if it is 0, both children removed, hence height decreased
        // If its not 0, means one child removed, other exists
        // Hence, height has not yet decreased
        if (current->balance != 0)
          heightDecreased = false;
      }
    }
    else
    {
      /**
        * The value is found, so we have to remove it from the tree
        * For this, we need to check a few scenarios
        */

      // Scenario 1: The current node does not have left or right
      if (nullptr == current->left && nullptr == current->right)
      {
        // We simply delete the node and return null
        delete current;
        heightDecreased = true;
        return nullptr;
      }

      // Scenario 2: The current node has left but no right
      if (nullptr != current->left && nullptr == current->right)
      {
        // In this case the left of current will be orphaned
        Node *orphan = current->left;

        // Delete the current node and return orphan
        delete current;
        heightDecreased = true;
        return orphan;
      }

      // Scenario 3: The current node has right but no left
      if (nullptr == current->left && nullptr != current->right)
      {
        // In this case the right of current will be orphaned
        Node *orphan = current->right;

        // Delete the current node and return orphan
        delete current;
        heightDecreased = true;
        return orphan;
      }

      // Scenario 4: The current has both, left and right

      /**
        * To delete the current node, we will have to get 
        * its successor (next higher value in the tree)
        * or predecessor (next lower value in the tree)
        * and replace current with it
        */

      // Let's find the successor
      // Successor is define as left most node of the right subtree
      // Predecessor is defined as right mode node of the left subtree
      Node *successor = current->right;
      while (successor->left != nullptr)
        // Keep going left
        successor = successor->left;

      // We have found the successor and it can be null
      // Because, had it been null, it would be scenario 1 or 2

      // Now lets replace the current value with successor value
      current->value = successor->value;

      // But now we have the same value twice in the tree
      // We can remove the successor instead, by calling removeNode
      current->right = removeNode(current->right, successor->value, heightDecreased);
      if (heightDecreased == true)
      {
        current->balance--;
        if (current->balance != 0)
          heightDecreased = false;
      }
    }

    // AVL: Change required for AVL balance tree
    current = rebalance(current);

    return current;
  }

public:
  // Data Abstractor method for remove
  void remove(int valToRemove)
  {
    bool heightDecreased = false;
    root = removeNode(root, valToRemove, heightDecreased);
  }

private:
  // inorderAscending method for printing the tree
  void inorderAscending(Node *current)
  {
    // If we reach null, we unwind back
    if (nullptr == current)
      return;

    // If not, lets visit left child firstenter program name, for example ${workspaceFolder}
    inorderAscending(current->left);

    // Now print the current value
    cout << current->value << endl;

    // Visit the right child
    inorderAscending(current->right);
  }

public:
  // Data abstractor for inorderAscending
  void printAscending()
  {
    inorderAscending(root);
  }

private:
  void inorderDebug(Node *current)
  {
    static int level = 0; // The amount of indentation
    if (current)
    {
      level++;
      inorderDebug(current->right);
      cout << setw(level * 4) << " " << current->value
           << " [" << current->balance << "] " << endl;
      inorderDebug(current->left);
      level--;
    }
  }

public:
  void printDebug()
  {
    inorderDebug(root);
  }
};
