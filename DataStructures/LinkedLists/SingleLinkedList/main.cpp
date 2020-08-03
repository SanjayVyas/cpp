/*
 * ----------------------------------------------------------------------
 * File:      main.cpp
 * Project:   SingleLinkedList
 * Author:    Sanjay Vyas
 * 
 * Description:
 *  Test driver for SingleLinkedList
 * ----------------------------------------------------------------------
 * Revision History:
 * 2020-Aug-04	[SV]: Created
 * ----------------------------------------------------------------------
 */

#include <iostream>
#include <cctype>
#include "SingleLinkedList.h"
using namespace std;

int main()
{
  int userval;
  List myList;

  while (cout << "Enter a value (0 to stop): ",
         cin >> userval,
         userval)
  {
    char where;
    bool added;

    cout << "Add to (B) or (F): ";
    cin >> where;

    if (toupper(where) == 'B')
    {
      added = myList.addToBack(userval);
      if (!added)
        cerr << "Error: could not add value" << endl;
    }

    else if (toupper(where) == 'F')
    {
      added = myList.addToFront(userval);
      if (!added)
        cerr << "Error: could not add value" << endl;
    }

    else
    {
      cerr << "Error: Value not added. Please specify B or F" << endl;
    }
  }
}
