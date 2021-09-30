
#ifndef LINKEDLIST
#define LINKEDLIST 

//for header files
#include <string>
//for function implementation

typedef std::string ItemType;
struct Node
{
    ItemType value;
	Node* next; 
};
class LinkedList {
private:
	Node* head;
	
	
public:
	LinkedList(); // constructor

	LinkedList(const LinkedList& rhs); // copy constructor 

	// Destroys all the dynamically allocated memory// in the list.
	~LinkedList();

	// assignment operator
	const LinkedList& operator=(const LinkedList& rhs);

	// Inserts val at the front of the list
	void insertToFront(const ItemType &val);

	// Prints the LinkedList
	void printList() const;

	// Sets item to the value at position i in this
	// LinkedList and return true, returns false if 
	// there is no element i 
	bool get(int i, ItemType& item) const;

	// Reverses the LinkedList
	 void reverseList();

	// Prints the LinkedList in reverse order
	void printReverse() const;

	// Appends the values of other onto the end of this LinkedList.
	void append(const LinkedList &other);

	// Exchangethe contents of this LinkedList with the other one.
	void swap(LinkedList &other);

	// Returns the number of items in the Linked List.
	int size() const;
};
#endif 