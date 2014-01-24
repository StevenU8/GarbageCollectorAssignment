#ifndef MY_LIST_H
#define MY_LIST_H

#include "RecordMemoryPool.h"

//
// class: MyList
//
// simple link list of integers. Instead of relying on system memory support, we must
// allocate memory from the RecordMemoryPool object.
//
class MyList{
	private:
		RecordMemoryPool&	 mRecordPool;		// Memory manager for this list
		MemoryAddress        mHeadPointer;		// head of the list

		int					 mNumOps;
								//
								// Remembers how many times the user have performed
								// operations on this link list.
								//
								// Each Operation is either an insert or delete
								// Unsuccessful deletion is also recorded as a valid op
								//

	public:

//===================================================================================
		// Constructor: this is the constructor:
		// precondition: pool must be a proper RecordMemoryPool with proper memory
        // postcondition: supports proper operation of list
		MyList(RecordMemoryPool &pool) :
				mNumOps(0),
				mRecordPool(pool),						// initialize record pool
				mHeadPointer(kNullAddress)	 			// initialize HeadPointer to NULL
			{}		

//===================================================================================
//      Accessor
//===================================================================================
        // HeadOfList: 
        // precondition: none
        // postcondition: returns the first element of the link list
		MemoryAddress HeadOfList() const {
				return mHeadPointer;
		}

        // NumOpsPerformed: 
        // precondition: none
        // postcondition: returns the number of operations performed
        //      includes: all insertion (even if out of memory and no actual insertion happened)
        //                all deletion (including key not found)
        int			NumOpsPerformed() const { return mNumOps; }

//===================================================================================
//      Mutator: simple insert/remove methods
//===================================================================================
		//
        // InsertElement: 
        // precondition: properly initialized
        // postcondition: insert key into the list
        //      Memory will be requested from the RecordMemoryPool
        //      if out of memory: warn the user and ignore the command
        //      O(1) operation, insert to the front of the list
		void 		InsertElement(int Key);
					
        // RemoveLinkFromList: 
        // precondition: properly initialized
        // postcondition: remove the link that contains "key" from the linked list
        //      no need to "delete" memory, simply remove it.
        //      return true (successful deletion) or false (key not found)
        //      when key not found, list is not altered.
		bool		RemoveLinkFromList(int Key);    
					
//===================================================================================
//      Utilities: Print and sort
//===================================================================================
		// PrintListContent: 
        // precondition: properly initialized
        // postcondition: print the keys and the next field of all records in the list
        void		PrintListContent(const char* listName);
		
        // SortList: 
        // precondition: properly initialized
        // postcondition: Perform mergeSort to sort the list
        void		SortList();
		
};

#endif
