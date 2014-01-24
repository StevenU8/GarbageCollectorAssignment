/////////////////////////////////////////////////////////////////
//
// File: hw7.cpp
// Author: Kelvin Sung
// Date: Nov 2013
//
// CSS501: hw7 test shell.
// Please DO NOT change this file! You do not have to submit this file!
//

#include <iostream>
using namespace std;

#include "RecordMemoryPool.h"
#include "MyList.h"

const char kQuitCmd = 'q';
const char kInsertCmd = 'i';
const char kDeleteCmd = 'd';
const char kPrintListCmd = 'p';
const char kGarbageCollectionCmd = 'g';
const char kPrintMemoryPoolCmd = 'f';
const char kSortListCmd = 's';



void main()
{
	char cmd = NULL;
	int  inputNum, numRecords;

    cout << "Please enter number of records for the pool: ";
    cin >> numRecords;

    RecordMemoryPool pool(numRecords);
	//RecordMemoryPool *pool = new RecordMemoryPool(numRecords);
	MyList myList(pool);


	cmd = kPrintListCmd;
	do {
		cout << "\nYour Command [" << 
				kInsertCmd << " " <<
                kDeleteCmd << " " <<
                kPrintListCmd << " " <<
                kGarbageCollectionCmd << " " <<
                kPrintMemoryPoolCmd << " " << 
                kSortListCmd << "]? ";
		cin >> cmd;

		switch (cmd) {
			case kInsertCmd:
					//
					// insert until we see -1
					//
					cout << "Please enter integers to be inserted (-1 to stop)" << endl;
					cin >> inputNum;
					while (inputNum >= 0) {
						myList.InsertElement(inputNum);
						cin >> inputNum;
					}
					break;

			case kDeleteCmd:
					//
					// enter one element and delete
					//
					cout << "Please enter the key to delete: ";
					cin >> inputNum;

					if ( myList.RemoveLinkFromList(inputNum) ) {
						cout <<  "Deleted Key(" << inputNum << ")" << endl;
					} else  {
						cout << "Input: [" << inputNum << "] is not in the list!" << endl;
					}
                    break;
					
			case kPrintListCmd:
					//
					// print the keys in the list, then print the 
					// content of the list;
					myList.PrintListContent("myList");
					break;
			
			case kGarbageCollectionCmd:
					//
					// force a garbage collection
					cout << "Forcing a garbage collection!\n";
					pool.GarbageCollection(myList.HeadOfList());
					break;
			
            case kPrintMemoryPoolCmd:
					//
					// print record pool
					cout << "Here is the Record Pool:" << endl;
					pool.PrintRecordMemoryPool();
					break;

			case kSortListCmd:
					//
					// 
					myList.SortList();
					break;

			default:
					break;
		} 
	} while (cmd != kQuitCmd);
}