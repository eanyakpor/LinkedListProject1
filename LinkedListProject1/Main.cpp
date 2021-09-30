
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <csignal>
#include <regex>
#include <type_traits>
#include <set>
#include <iostream>
#include "LinkedList.h"
using namespace std;
class streambuf_switcher
{
public:
	streambuf_switcher(ios& dest, ios& src)
		: dest_stream(dest), saved_streambuf(dest.rdbuf(src.rdbuf()))
	{}
	~streambuf_switcher()
	{
		dest_stream.rdbuf(saved_streambuf);
	}
private:
	ios& dest_stream;
	streambuf* saved_streambuf;
};
set<void*> addrs;
bool recordaddrs = false;

void* operator new(size_t n)
{
	void* p = malloc(n);
	if (recordaddrs && n == sizeof(Node))
	{
		recordaddrs = false;
		addrs.insert(p);
		recordaddrs = true;
	}
	return p;
}

void operator delete(void* p) noexcept
{
	if (recordaddrs)
	{
		recordaddrs = false;
		set<void*>::iterator it = addrs.find(p);
		if (it != addrs.end())
			addrs.erase(it);
		recordaddrs = true;
	}
	free(p);
}
void operator delete(void* p, std::size_t s) noexcept
{
	s = addrs.size();   // these two lines do nothing other than 
	s += s;               // getting rid of unused var warning on g++
	if (recordaddrs)
	{
		recordaddrs = false;
		set<void*>::iterator it = addrs.find(p);
		if (it != addrs.end())addrs.erase(it);
		recordaddrs = true;
	}
	free(p);
}void testone(int n)
{
	LinkedList empty;
	LinkedList l1;
	l1.insertToFront("9");
	l1.insertToFront("8");
	l1.insertToFront("7");
	LinkedList l2;
	l2.insertToFront("4");
	l2.insertToFront("3");
	ItemType x;
	switch (n)
	{
	default: {
		cout << "Bad argument" << endl;
	}
		   break;
	case 1:
	{
		assert(empty.size() == 0);
	}
	break;
	case 2: {
		assert(l1.size() == 3);
	}
		  break;
	case 3: {
		assert(!empty.get(0, x));
	}
		  break;
	case 4: {
		assert(l1.get(0, x) && x == "7");
	}
		  break;
	case 5: {
		assert(l1.get(2, x) && x == "9");
	}
		  break;
	case 6: {
		assert(!l1.get(3, x));
	}
		  break;
	case 7: {
		LinkedList l3(l1);
		assert(l3.size() == 3);
		assert(l1.size() == 3);
		assert(l1.get(1, x) && x == "8");
	}
		  break;
	case 8: {
		LinkedList l3;
		l3 = l1;
		assert(l3.size() == 3);
		assert(l1.size() == 3);
		assert(l1.get(1, x) && x == "8");
	}
		  break;
	case 9: {
		LinkedList l3(empty);
		assert(l3.size() == 0);
	}
		  break;
	case 10: {
		l1.reverseList();
		assert(l1.get(0, x) && x == "9");
	}
		   break;
	case 11: {
		l1.reverseList();
		assert(l1.get(2, x) && x == "7");
	}
		   break;
	case 12: {
		empty.reverseList();
		assert(empty.size() == 0);
	} break;
	case 13: {
		ostringstream strCout;
		streambuf_switcher sso(cout, strCout);
		l1.printList();
		string str = strCout.str();
		regex e("7.*8.*9"); // 7 followed by 8 followed by 9
		assert(regex_search(str, e));
	}
		   break;
	case 14:
	{
		ostringstream strCout;
		streambuf_switcher sso(cout, strCout);
		l1.printReverse();
		string str = strCout.str();
		regex e("9.*8.*7"); // 9 followed by 8 followed by 7
		assert(regex_search(str, e));// make sure they didn't take off const after printReverse
		assert((is_same<decltype(&LinkedList::printReverse),
			void (LinkedList::*)() const>::value));
	}
	break;
	case 15: {
		recordaddrs = true;
		{
			LinkedList l;
			int oldn = addrs.size();
			l.insertToFront("1");
			l.insertToFront("1");
			l.insertToFront("1");
			l.insertToFront("1");
			assert(addrs.size() == oldn + 4);
		}
		assert(addrs.size() == 0); recordaddrs = false;
	}
		   break;
	case 16: {
		recordaddrs = true;
		int oldn = addrs.size();
		l1.append(l2);
		assert(addrs.size() == oldn + 2);
		assert(l1.size() == 5);
		assert(l1.get(0, x) && x == "7");
		assert(l1.get(4, x) && x == "4");
		recordaddrs = false;
	}
		   break;
	case 17: {
		LinkedList l;
		recordaddrs = true;
		int oldn = addrs.size();
		l.append(l2);
		assert(l.size() == 2);
		assert(l2.size() == 2);
		assert(addrs.size() == oldn + 2);
		recordaddrs = false;
	}
	break; 
	case 18: {
		l1.swap(l2);
		assert(l1.size() == 2);
		assert(l2.size() == 3);
		assert(l1.get(0, x) && x == "3");
		assert(l1.get(1, x) && x == "4");
		assert(l2.get(0, x) && x == "7");
		assert(l2.get(2, x) && x == "9");
	}
	break;
	case 19: {
		LinkedList l;
		l1.swap(l);
		assert(l.size() == 3);
		assert(l.get(0, x) && x == "7");
		assert(l1.size() == 0);
		assert(!l1.get(0, x));
	}
	break;
	case 20: {
		int oldn = 0;
		{
			LinkedList l;
			recordaddrs = true;
			oldn = addrs.size();
			l.insertToFront("1");
			assert(l.size() == 1);
			assert(addrs.size() == oldn + 1);
		}
		assert(addrs.size() == 0);
		recordaddrs = false; } break;
	}
}
int main() {
	cout << "Enter test number: ";
	int n; cin >> n; testone(n);
	cout << "Passed" << endl;
}
	/*
		//for reversing list
		LinkedList ls;
		ls.insertToFront("The Mandalorian");
		ls.insertToFront("Baby Yoda");
		ls.insertToFront("Cara Dune");
		ls.insertToFront("Greef Karga");
		ls.printReverse();
		// for get function
		LinkedList list;
		list.insertToFront("Hawkeye");
		list.insertToFront("Thor");
		list.insertToFront("Hulk");
		list.insertToFront("Black Widow");
		list.insertToFront("Iron Man");
		list.insertToFront("Captain America");
		for (int k = 0; k < list.size(); k++) {
			string x;
			list.get(k, x);
			cout << x << endl;
		}
		LinkedList e1;
		e1.insertToFront("Athos");
		e1.insertToFront("Porthos");
		e1.insertToFront("Aramis");
		LinkedList e2;
		e2.insertToFront("Robin");
		e2.insertToFront("Batman");
		e1.append(e2);  // adds contents of e2 to the end of e1
		e1.printList();
		string a;
		assert(e1.size() == 5  &&  e1.get(3, a)  &&  a == "Batman");
		assert(e2.size() == 2  &&  e2.get(1, a)  &&  a == "Robin");
		//for swap method
		LinkedList e3;
		e3.insertToFront("A");
		e3.insertToFront("B");
		e3.insertToFront("C");
		e3.insertToFront("D");
		LinkedList e4;
		e4.insertToFront("X");
		e4.insertToFront("Y");
		e4.insertToFront("Z");
		e3.swap(e4);  // exchange contents of e1 and e2
		string b;
		assert(e3.size() == 3  &&  e3.get(0, b)  &&  b == "Z");
		assert(e4.size() == 4  &&  e4.get(2, b)  &&  b == "B");
		*/


