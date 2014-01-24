#include <iostream>
#include <iomanip>
#include "RecordMemoryPool.h"

using namespace std;

// record size
static const int kRecordSize = 3;

static const int Free = 0;
static const int InUse = 1;

// Constructor
// precondition: 
//          n number of records to be defined in the memory pool.
//          this is the only place we can "new" memory in this hw
// postcondition: n is the number of Records to be defined in the integer array mRecordMemory. 
//      mRecordMemory is the memory we will manage.
RecordMemoryPool::RecordMemoryPool(int n) 
{
    mNumRecords = n;

	mMemorySize = mNumRecords * kRecordSize;

    mRecordMemory = new int[mMemorySize];

	for (int i=2; i<mMemorySize; i+=kRecordSize) {
		mRecordMemory[i] = Free;
	}

    // you can add in your own instance variable initialization
}

RecordMemoryPool::~RecordMemoryPool()
{
    if (NULL != mRecordMemory)
        delete [] mRecordMemory;
}



// GarbageCollection: find all unused memory
// precondition: mCurrentRecord is properly initialized
// postcondition: all unused records' MMField will be set to eRecordIsFree
//  This is accomplished by following the headPtr, and marking all links pointed to
//  by the headPtr as in use. Everything else is free.
void RecordMemoryPool::GarbageCollection(MemoryAddress headPtr) 
{

	//mark all as free
	for (int i=2; i<mMemorySize; i+=kRecordSize) {
		mRecordMemory[i] = Free;
	}

	//follow head and mark as InUse
	bool endOfList = false;
	MemoryAddress curPtr = headPtr;
	while (!endOfList && headPtr != kNullAddress) {
		if (mRecordMemory[curPtr + 1] == kNullAddress) { endOfList = true; }
		mRecordMemory[curPtr + 2] = InUse;
		curPtr = mRecordMemory[curPtr + 1];
	}

}



// NextFreeRecord: Returns the next free record, if there is one
// precondition:properly initialized. 
//      headPtr: is the pointer to the head of the link list, 
//          GarbageCollection should only be trigger if cannot trivially find 
//          free record
// postcondition:
//      returns the address (index) of a free record. 
//      Returns kNullAddress if out of memory.
MemoryAddress RecordMemoryPool::NextFreeRecord(MemoryAddress headPtr) 
{
	bool collected = false;

	for (int i = 0; i < 2; i++) {
	
		//loop through and find unused memory
		for (int i=2; i<mMemorySize; i+=kRecordSize) {
			if (mRecordMemory[i]==Free) {
				return i - 2 ;
			}
		}

		//if unused memory is not found, call garbage collector
		if (collected == false) {
			GarbageCollection(headPtr);
			collected = true;
		}
	}

	return kNullAddress;
}


// PrintRecordMemoryPool: Prints out the entire memory pool
// precondition: properly initialized
// postcondition: prints out the memory from small location to the larger locations
void RecordMemoryPool::PrintRecordMemoryPool()
{
	cout << "Record Memory Pool Content: " << endl;
	for (int i=0; i<mMemorySize; i+=kRecordSize) {
		cout << "Memory: ["  << setw(2) << i
		     << "]: Record(" << setw(2) << i / kRecordSize
			 << "): Key="    << setw(5) << mRecordMemory[i]
			 << "  Next="    << setw(5) << mRecordMemory[i + 1]
			 << "  MM="      << ((mRecordMemory[i + 2]==Free) ? "Free" : "InUse") << endl;
	}
}





// SetRecord: add to linked list
// precondition: properly initialized
// postcondition: sets a record and adds it to the linked list
void RecordMemoryPool::SetRecord(MemoryAddress &headPtr, MemoryAddress targetPtr, int key)
{
	
	if (headPtr == kNullAddress) {
		mRecordMemory[targetPtr + 1] = -1;
	} else {
		mRecordMemory[targetPtr + 1] = headPtr;
	}

	mRecordMemory[targetPtr] = key;
	mRecordMemory[targetPtr + 2] = InUse;
	headPtr = targetPtr;
}

// DisplayList: display linked list
// precondition: properly initialized
// postcondition: traverses linked list and prints out each "node"
void RecordMemoryPool::DisplayList(const MemoryAddress &headPtr) {
	bool endOfList = false;
	MemoryAddress curPtr = headPtr;
	while (!endOfList && headPtr != kNullAddress) {
		if (mRecordMemory[curPtr + 1] == kNullAddress) { endOfList = true; }
		cout << "\tRecordAdddress("  << setw(2) << curPtr << ")  "
			<< "Key=(" << setw(5) << mRecordMemory[curPtr] << ") "
			<< "NextRecordAddress=" << setw(3) << mRecordMemory[curPtr + 1]
			<< endl;
		curPtr = mRecordMemory[curPtr + 1];
	}
}


// Remove: removes a node from the linked list
// precondition: properly initialized
// postcondition: finds key and removes it from linked list
bool RecordMemoryPool::Remove(MemoryAddress &headPtr, int key) {
	bool endOfList = false;
	MemoryAddress prevPtr;
	MemoryAddress curPtr = headPtr;
	MemoryAddress nextPtr = mRecordMemory[curPtr + 1];
	while (!endOfList && headPtr != kNullAddress) {
		if (mRecordMemory[curPtr] == key) { 
			if (curPtr == headPtr) {
				headPtr = nextPtr;
			} else {
				mRecordMemory[prevPtr + 1] = nextPtr;
			}
			return true;
		}
		if (mRecordMemory[curPtr + 1] == kNullAddress) { endOfList = true; }
		
		prevPtr = curPtr;
		curPtr = nextPtr;
		nextPtr = mRecordMemory[curPtr + 1];
	}
	return false;
}

// SortList: sort the linked list from smallest to largest
// precondition: properly initialized
// postcondition: head points to the first node in the sorted linked list
void RecordMemoryPool::SortList(MemoryAddress &headPtr) 
{
	MemoryAddress tempHead = headPtr;
	MemoryAddress a;
	MemoryAddress b;

	//If head is NULL or there is only one element in the Linked List then return.
	if (mRecordMemory[headPtr] == kNullAddress || mRecordMemory[headPtr + 1] == kNullAddress) {
		return;
	} else {
		SplitList(tempHead, a, b); 
		SortList(a);
		SortList(b);
		mergeList(headPtr, a, b);
	}
}














//private function used for sorting the list

// mergeList: merge two lists
// precondition: properly initialized. each list is already sorted
// postcondition: linked lists are merged in a sorted fashion.
void RecordMemoryPool::mergeList(MemoryAddress &headPtr, MemoryAddress &a, MemoryAddress &b)
{

    // special case for empty lists
    if (mRecordMemory[a] == kNullAddress) {
        headPtr = b;
        b = kNullAddress;
        return;
    } else if (mRecordMemory[b] == kNullAddress) {
        headPtr = a;
        a = kNullAddress;
        return;
    }
    
    MemoryAddress ptr1 = a;
    MemoryAddress ptr2 = b;
    a = kNullAddress;
    b = kNullAddress;
    
    // now take care of head

    if (mRecordMemory[ptr1] < mRecordMemory[ptr2]) {
        headPtr = ptr1;
        ptr1 = mRecordMemory[ptr1 + 1];
    } else {
        headPtr = ptr2;
        ptr2 = mRecordMemory[ptr2 + 1];
    }

    MemoryAddress ptr3 = headPtr;

    // now the lists
    while ((kNullAddress != ptr1) && (kNullAddress != ptr2)) {
        if (mRecordMemory[ptr1] < mRecordMemory[ptr2]) {
            mRecordMemory[ptr3 + 1] = ptr1;
            ptr3 = ptr1;
            ptr1 = mRecordMemory[ptr1 + 1];
        } else {
            mRecordMemory[ptr3 + 1] = ptr2;
            ptr3 = ptr2;
            ptr2 = mRecordMemory[ptr2 + 1];
        }
    }

    // now, collect remaining
    if (ptr1 == kNullAddress) {
        mRecordMemory[ptr3 + 1] = ptr2;
	} else {
        mRecordMemory[ptr3 + 1] = ptr1;
	}
}


// SplitList: split list into two
// precondition: properly initialized
// postcondition: sets a and b equal to the first node in each list.
void RecordMemoryPool::SplitList(MemoryAddress &tempHead, MemoryAddress &a, MemoryAddress &b) 
{

	MemoryAddress curr;
	MemoryAddress next;

	if (tempHead == kNullAddress || mRecordMemory[tempHead + 1] == kNullAddress) {
		a = tempHead;
		b = kNullAddress;
	} else {
		curr = tempHead;
		next = mRecordMemory[tempHead + 1];
		while (next != kNullAddress) {
			next = mRecordMemory[next + 1];
			if (next != kNullAddress) {
				curr = mRecordMemory[curr + 1];
				next = mRecordMemory[next + 1];
			}
		}

		a = tempHead;
		b = mRecordMemory[curr + 1];
		mRecordMemory[curr + 1] = kNullAddress;
	}
}

