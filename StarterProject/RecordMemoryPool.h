#ifndef RECORD_MEMORY
#define RECORD_MEMORY

typedef int MemoryAddress;
const int kNullAddress = -1;


//
// Pool of record memory: 
//
// 	Design to support one link list of IntegerRecords.
// 	An IntergerRecord is defined as:
//
// 		Offset - 0: Key
// 		Offset - 1: Next "Pointer to next IntegerRecord"
// 		Offset - 2: Reserved for Memory management
//  
// This class has the notion of:
//
//			Record - there are mNumRecord number of records
//
// We can get the address of each record
// by calling the RecordAddress() function.
//
// E.g. I want to work with record number 6, then, I will call 
//
//			RecordAddress(6) to the the address of record number 6
//			(which in this case is index-18).
//
//
// The reason for using the notion of "Record" as a "unit" is because _ALL_ our algorithms
// are based on how many "records" we have, e.g.
//				find a free "Record", 
//				mark all "Record" to be free
//
// All iterations will fit naturally with advancing the memory pool in units
// of Records.
//
// This is assumed to be low level (OS-level) function. NO ERROR checking will be performed. 
// Any attempts at accessing array index outside of bound will simply crash the program.
// Use with care.
//
class RecordMemoryPool {
	private:
        
        // this is the memory array!
		int	*mRecordMemory;
        int mNumRecords;

		int mMemorySize;

		// SplitList: split list into two
		// precondition: properly initialized
		// postcondition: sets a and b equal to the first node in each list.
		void SplitList(MemoryAddress &tempHead, MemoryAddress &a, MemoryAddress &b);

		// mergeList: merge two lists
		// precondition: properly initialized. each list is already sorted
		// postcondition: linked lists are merged in a sorted fashion.
		void mergeList(MemoryAddress &headptr, MemoryAddress &a, MemoryAddress &b);

	public:
//=============================================================
//          constructor and destructor
//-----------------------------------------------------------------
		// Constructor
        // precondition: 
        //          n number of records to be defined in the memory pool.
        //          this is the only place we can "new" memory in this hw
        // postcondition: n is the number of Records to be defined in the integer array mRecordMemory. 
        //      mRecordMemory is the memory we will manage.
        RecordMemoryPool(int n);
        // Destructor        
        ~RecordMemoryPool();

//=============================================================
//      Memory manager utility
//---------------------------------------------------------------
        // GarbageCollection: find all unused memory
        // precondition: mCurrentRecord is properly initialized
        // postcondition: all unused records' MMField will be set to eRecordIsFree
        //  This is accomplished by following the headPtr, and marking all links pointed to
        //  by the headPtr as in use. Everything else is free.
		void GarbageCollection(MemoryAddress headPtr);
			
        // NextFreeRecord: Returns the next free record, if there is one
        // precondition:properly initialized. 
        //      headPtr: is the pointer to the head of the link list, 
        //          GarbageCollection should only be trigger if cannot trivially find 
        //          free record
        // postcondition:
        //      returns the address (index) of a free record. 
        //      Returns kNullAddress if out of memory.
		MemoryAddress NextFreeRecord(MemoryAddress headPtr);
			
//=============================================================
//      General debug utility:
//---------------------------------------------------------------
        // PrintRecordMemoryPool: Prints out the entire memory pool
        // precondition: properly initialized
        // postcondition: prints out the memory from small location to the larger locations
        //      You should clearly indicate the _CURRENT_ state of the memory system.
        //      For example, if a record is allocated and removed from a link list
        //      the record should print as "InUse" until the next time a garbage collection
        //      occurred.
		void PrintRecordMemoryPool();

		// SetRecord: add to linked list
		// precondition: properly initialized
		// postcondition: sets a record and adds it to the linked list
		void SetRecord(MemoryAddress &headPtr, MemoryAddress targetPtr, int key);

		// DisplayList: display linked list
		// precondition: properly initialized
		// postcondition: traverses linked list and prints out each "node"
		void DisplayList(const MemoryAddress &headPtr);

		// Remove: removes a node from the linked list
		// precondition: properly initialized
		// postcondition: finds key and removes it from linked list
		bool Remove(MemoryAddress &headPtr, int key);

		// SortList: sort the linked list from smallest to largest
		// precondition: properly initialized
		// postcondition: head points to the first node in the sorted linked list
		void SortList(MemoryAddress &mHeadPointer);


};

#endif