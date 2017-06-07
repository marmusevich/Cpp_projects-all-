#include <iostream>
#include <string>
#include <sstream>
#include "catalog.h"
#include "unittest.h"


using namespace std;


UnitTest (testDefaultConstructor)
{
	Catalog c;
	assertEqual (0, c.size());
	assertEqual (100, c.capacity());
	assertFalse (c.contains("abc"));
	assertEqual (Book(), c.get("abc"));
	assertEqual (Book(), c.get(0));

	Catalog c2(40);
	assertEqual (c, c2);
	assertFalse (c < c2);
}

UnitTest (testConstructor )
{
	Catalog c(50);
	assertEqual (0, c.size());
	assertEqual (50, c.capacity());
	assertFalse (c.contains("abc"));
	assertEqual (Book(), c.get("abc"));
	assertEqual (Book(), c.get(0));

	Catalog c2(40);
	assertEqual (c, c2);
	assertFalse (c < c2);
}

UnitTest(testReserve)
{
	Catalog c(50);
	c.add(Book("1", "Jones", "A Primer on C++"));
	c.add(Book("2", "Smith", "A Primer on Java"));
	assertEqual (50, c.capacity());
	assertEqual (2, c.size());
	Catalog c2 = c;
	c2.reserve(99);
	assertTrue (c2.capacity() >= 99);
	assertEqual (2, c2.size());
	assertEqual (c2, c);

	c2.reserve(1);
	assertTrue (c2.capacity() >= c2.size());
	assertEqual (2, c2.size());
	assertEqual (c2, c);
}

UnitTest(testAddBasic)
{
	Book b1 ("1", "Jones", "A Primer on C++");
	Book b1a ("1", "Smith", "A Primer on Java");
    Book b3 ("3", "Jones", "A Primer on C++");
    Book b5 ("5", "Adams", "Advanced C++");

	Catalog c(50);
	c.add(b1);
	assertEqual (1, c.size());
	c.add(b5);
	assertEqual (2, c.size());
	c.add(b1a);
	assertEqual ("1", c.get(0).getID());
	assertEqual (b1a.getTitle(), c.get(0).getTitle());
	assertEqual (2, c.size());
	c.add(b3);
	assertEqual (3, c.size());
	assertEqual (b1a, c.get(0));
	assertEqual (b3, c.get(1));
	assertEqual (b5, c.get(2));

	assertNotEqual (c, Catalog());

	assertTrue (c.contains("1"));
	assertFalse (c.contains("2"));
	assertTrue (c.contains("3"));
	assertTrue (c.contains("5"));
}

UnitTest(testAddCapacity)
{
	Catalog cat(16);

	int cap = cat.capacity();
	for (int i = 0; i < cap; ++i) {
	  ostringstream out1;
	  out1 << i;
	  string is = out1.str();
	  Book b ("key" + is, "Author " + is, "Title: " + is);
	  cat.add (b);
	}

	assertEqual (cap, cat.size());
	assertEqual (cap, cat.capacity());

	Book b1 ("0000", "Jones", "His Book");
	cat.add (b1);

	assertEqual (cap+1, cat.size());
	assertTrue (cat.capacity() > cap);
	assertTrue (cat.contains("0000"));
}


UnitTest(testCopy)
{
	Book b1 ("1", "Jones", "A Primer on C++");
	Book b1a ("1", "Smith", "A Primer on Java");
    Book b3 ("3", "Jones", "A Primer on C++");
    Book b4 ("4", "Jones", "A Primer on C++");
    Book b5 ("5", "Adams", "Advanced C++");

	Catalog c(50);
	c.add(b1);
	c.add(b5);
	c.add(b3);


	Catalog c2 (c);

	assertEqual (c2, c);
	assertEqual (3, c2.size());
	assertEqual (b1, c2.get(0));
	assertEqual (b3, c2.get(1));
	assertEqual (b5, c2.get(2));

	c.add(b4);

	assertNotEqual (c2, c);
	assertEqual (3, c2.size());
	assertEqual (b1, c2.get(0));
	assertEqual (b3, c2.get(1));
	assertEqual (b5, c2.get(2));

}


UnitTest(testAssign)
{
	Book b1 ("1", "Jones", "A Primer on C++");
	Book b1a ("1", "Smith", "A Primer on Java");
    Book b3 ("3", "Jones", "A Primer on C++");
    Book b4 ("4", "Jones", "A Primer on C++");
    Book b5 ("5", "Adams", "Advanced C++");

	Catalog c(50);
	c.add(b1);
	c.add(b5);
	c.add(b3);


	Catalog c2;
	Catalog c3 (c2 = c);

	assertEqual (c2, c);
	assertEqual (3, c2.size());
	assertEqual (b1, c2.get(0));
	assertEqual (b3, c2.get(1));
	assertEqual (b5, c2.get(2));

	assertEqual (c3, c);

	c.add(b4);

	assertNotEqual (c2, c);
	assertEqual (3, c2.size());
	assertEqual (b1, c2.get(0));
	assertEqual (b3, c2.get(1));
	assertEqual (b5, c2.get(2));


}





