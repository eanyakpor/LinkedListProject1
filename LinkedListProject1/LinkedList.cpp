#include "LinkedList.h"
//for function implementation


#include <iostream>
#include <string>
using namespace std;
typedef std::string ItemType;


//default constructor 
LinkedList::LinkedList() {
	head = nullptr;
}
//will be constructing a brand new linkedlist object
LinkedList::LinkedList(const LinkedList& rhs) {
	cout << "copy constructor has been called" << endl;
	//allocate a new node and set that as head
	Node* r = head;
	//probally need to create two heads to traverse both list 
	// add *temp to rhs linkedlist values as move through the list
	//traverse rhs linked list?
	while (r != nullptr) {
		//create a new node to insert values from one linked list to the other
		Node* temp = new Node;
		//new node gets a value from the linked list everytime it traverses
		temp->value = r->value;
		//temp->next = rhs.head; could possible need this 
		// so that i can traverse the rhs linked list add add values of r to temp.

		//move through the list until it reaches nullptr
		r = r->next;

	}
}



// //assignment operator
//returning a refrence to a linkedlist object
//so we can chain multiple linkedlist objects with the assignment operator
//passing in by constant refrence a linkedlist obj
const LinkedList& LinkedList::operator=(const LinkedList& rhs) {
	cout << "this is the assignment operator" << endl;
	//check for self assignment 
	// check for alising
	if (this == &rhs) {
		return *this;
	}
	//i need to copy rhs linkedlist and the values of the other linked list
	//lastly return *this
}
/*
* overriding an existing object with another existing object
* was for assignment operator
// two linked list objects.
	LinkedList l1;
	LinkedList l2;
	//use a method from each class to insert to front c and.
	l1.insertToFront("c");
	l2.insertToFront("d");
	//overiding an existing object with another existing object.
	l1 = l2;
*/



void LinkedList::insertToFront(const ItemType& val)
{
	//creates ptr variable
	Node* p;
	//dynamically allocates a new memory for p
	p = new Node;
	//set node to value next pointing node to value 
	p->value = val;
	// p is now pointing to heads address 
	p->next = head;
	// set head to p
	head = p;
}

void LinkedList::printList() const {
	//create new ptr
	Node* p;
	//print will start from head ptr. 
	p = head;
	//traveress the linkedlist
	while (p != nullptr) {
		//prints value everytime isn't nullptr
		cout << p->value << " ";
		//assigns ptr to next ptr	
		p = p->next;
	}
	cout << endl;
}
// Sets item to the value at position i in this
// LinkedList and return true, returns false if 
// there is no element i 
bool LinkedList::get(int i, ItemType& item) const {
	// counts how many time p points to next
	int count = 0;
	Node* p = head;
	//count how many times p is pointing to next while traversing non empty list
	while (p != nullptr) {
		if (i == count) {

			//assigns item
			item = p->value;
			return true;
		}
		else if (p == nullptr && i != count) {
			return false;
		}


		p = p->next;
		count++;
		// check if postitoin i equals count

	}
}

// Reverses the LinkedList
void LinkedList::reverseList() {
	//initialize current, previous and next ptr. 
	Node* cur;
	//making current be at he start of list
	cur = head;
	// declaring and assigning previous/next 
	Node* prev;
	Node* next;
	//making previous/next point to nothing atm. 
	prev = nullptr;
	next = nullptr;
	// traverse while LinkedList is not enpty
	while (cur != nullptr) {
		// define next as current pointing to next
		next = cur->next;
		// where reversing begins 
		cur->next = prev;
		// move ptrs a position ahead
		prev = cur;
		cur = next;
	}
	head = prev;
}


// Prints the LinkedList in reverse order
void LinkedList::printReverse() const {
	//initialize current, previous and next ptr. 
	Node* cur;
	//making current be at he start of list
	cur = head;
	// declaring and assigning previous/next 
	Node* prev;
	Node* next;
	//making previous/next point to nothing atm. 
	prev = nullptr;
	next = nullptr;
	// traverse while LinkedList is not enpty
	while (cur != nullptr) {
		// define next as current pointing to next
		next = cur->next;
		// where reversing begins 
		cur->next = prev;
		// move ptrs a position ahead
		prev = cur;
		cur = next;

	}
	// so traverse the list while list isn't empty
	while (prev != nullptr) {
		// print out previous value 
		cout << prev->value << " ";
		// try to make previous point backwards 
		prev = prev->next;

	}
}
// Appends the values of other onto the end of this LinkedList.
// its only printing the first linkedlist its not adding the last two at the end of the first
// linked list



void LinkedList::append(const LinkedList& other) {
	// make *p point to head so we know where start of list is. 
	//traverse the list until we get to the node before nullptr
	// make *n point to new node. assign &other to n->value
	// point to  n->next to last node, p.
	//set n to null ptr.
	// We need three temporary Node *'s
	// we need to point to head in other LinkedList and out LinkedList. 
	//updated:
	//declare two nodes
	Node* p = head;
	Node* o = other.head;
	//if list is empty
	if (p == nullptr) {
		//other list isn't empty
		//traverse the other list
		while (o != nullptr) {
			//must add node one by one
			//create a new node 
			Node* n = new Node;
			//set n's new node to the value of o n has o's value
			n->value = o->value;
			//if its the first and only node make sure nextptr points to nullptr
			n->next = nullptr;
			o = o->next;
			if (head == nullptr) {
				head = n;
				//signinfies beginning of our new list we created
				//placeholder p
				p = n;
			}
			p->next = n;
			//keeps track of list of the last node in the original list in order to link new node 
			//to that last node
			p = n;

			//initilaize head somewhere
			//im confused on why I need to traverse the other linked list 
			//do i need to traverse the list to add a new node to the orginal list
		}



	}
	else {
		//find last node in p's linkedlist
		//create a new node each time I want to add a value to the original list
		while (p->next != nullptr) { // for one of the cases p is nullptr

			p = p->next;

		}
		while (o != nullptr) {
			//must add node one by one
			//create a new node 
			Node* n = new Node;
			//set n's new node to the value of o n has o's value
			n->value = o->value;

			//set the originals list last node to new node
			p->next = n;
			//moves p  because p now has the added value of n to orginal list
			p = p->next;
			//now set p->next to nullptr
			//maintain integrity of the list
			p->next = nullptr;


			o = o->next;


		}
	}


}

void LinkedList::swap(LinkedList& other) {
	//declaring nodes
	Node* p = head;
	Node* o = other.head;
	Node* n = nullptr;

	//use n pointer to  point to heads address
	// use temporary pointer to point to the heads 
	// n is pointing to the address of head
	n = head;
	//head equals other head
	head = other.head;
	//other head = n
	other.head = n;


}



// Returns the number of items in the Linked List.
int LinkedList::size() const {
	Node* p;
	p = head;
	int count = 0;
	while (p != nullptr) {
		++count;
		p = p->next;

	}
	return count;

}

// destructor 
LinkedList::~LinkedList() {
	// pointers that should point to head of list
	Node* h;
	h = head;
	Node* m;
	// traverses if list is not enpty
	while (h != nullptr) {
		// m = head pointing to next
		m = h->next;
		//deletes memory h
		delete h;
		h = m;
	}
}



