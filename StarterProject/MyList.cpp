#include <iostream>
#include <iomanip>
using namespace std;

#include "MyList.h"


// InsertElement: 
// precondition: properly initialized
// postcondition: insert key into the list
//      Memory will be requested from the RecordMemoryPool
//      if out of memory: warn the user and ignore the command
//      O(1) operation, insert to the front of the list
void MyList::InsertElement(int key)
{
	mNumOps++;
    // Request memory from the RecordMemoryPool
	MemoryAddress ptr = mRecordPool.NextFreeRecord(mHeadPointer);
		
		// now we can perform insertion (you will!)
		if (ptr != kNullAddress) {
			mRecordPool.SetRecord(mHeadPointer, ptr, key);
		} else {
			cout << "**** WARNING ****: Out of memory: List insertion of " << key << " failed!!" << endl;
		}
}

// RemoveLinkFromList: 
// precondition: properly initialized
// postcondition: remove the link that contains "key" from the linked list
//      no need to "delete" memory, simply remove it.
//      return true (successful deletion) or false (key not found)
//      when key not found, list is not altered.
bool MyList::RemoveLinkFromList(int key) // link containing this data will be removed
{
	mNumOps++;

	return mRecordPool.Remove(mHeadPointer, key);
}

// PrintListContent: 
// precondition: properly initialized
// postcondition: print the keys and the next field of all records in the list
void MyList::PrintListContent(const char *listName)
{
	cout << "After: " << mNumOps 
	 	 << " Operations: content of " 
		 << listName << "-List: Head(" << mHeadPointer << ")" << endl;

	// print list content
	 mRecordPool.DisplayList(mHeadPointer);
} 


// SortList:
// precondition: properly initialized
// postcondition: sort the list from smallest key to largest key
void MyList::SortList() 
{  
	mRecordPool.SortList(mHeadPointer);
}