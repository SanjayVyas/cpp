/*-----------------------------------------------------------------------------*
 * Project:   OptimizedAVLTree
 * File:      main.c
 * Author:    Sanjay Vyas (sanjay.vyas+code.khazana@gmail.com)
 * 
 * Description:
 * 
 * Revision History:
 *    2018-May-23: Initial Creation
 * 
 * Disclaimer:
 *    This code may contain intentional and unintentional bugs
 *    There are no warranties of the code working correctly
 *----------------------------------------------------------------------------*/

#include "AVLOptimized.h"

int main()
{
    // Create a tree
    Tree ped;
    int userval;

    // Add values to the tree
    while (cout << "Enter a value to add (0 to stop): ",
           cin >> userval,
           userval)
    {
        ped.add(userval);
        ped.printDebug();
    }

    ped.printAscending();

    // Now remove values from the tree
    while (cout << "Enter a value to remove (0 to stop): ",
           cin >> userval,
           userval)
    {
        ped.remove(userval);
        ped.printDebug();
    }
    ped.printAscending();
}