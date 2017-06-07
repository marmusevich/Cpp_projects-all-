/*
 * catalog.cpp
 *
 *  Created on: Apr 10, 2017
 *      Author: zeil
 */

#include "catalog.h"
#include <algorithm>

using namespace std;


/**
 * A list of books, identified by Gutenberg ID.
 */
/**
 * Create a new empty catalog, capable of holding up to
 * maxCapacity books.
 *
 * @param maxCapacity maximum number of books this catalog
 *    can hold.
 */
Catalog::Catalog (int maxCapacity)
{
//	theCapacity = maxCapacity;
//	theSize = 0;
//	books = new Book[theCapacity];
	 //books = new std::vector<Book>(maxCapacity);
	 books = std::vector<Book>(maxCapacity);
}






/**
 * How many books currently in this catalog?
 *
 * @return number of books in the catalog.
 */
int Catalog::size() const
{
	//return theSize;
	return books.size();

}

/**
 * How many books can this catalog hold?
 *
 * @return max capacity of this catalog.
 */
int Catalog::capacity() const
{
	//return theCapacity;
	return books.capacity();

}

/**
 * Attempt to alter the capacity of this catalog so that
 * it can hold at least newCapcity books.  Existing books
 * in the catalog are retained.
 *
 * @param newCapacity maximum number of books we would like to be able
 *    to store in this catalog.
 * @post capacity() >= newCapacity
 */
void Catalog::reserve (int newCapacity)
{
//	if (newCapacity >= theSize)
//	{
//		// Allocate a new array for the books.
//		Book* newBooks = new Book[newCapacity];
//		// Copy the books over to the new array.
//		for (int i = 0; i < theSize; ++i)
//		{
//			newBooks[i] = books[i];
//		}
//		// Update member variables
//		theCapacity = newCapacity;
//		delete [] books;
//		books = newBooks;
//	}

        books.reserve(newCapacity);

}

/**
 * Add a book to the catalog. If a book with the same ID exists, it is
 * replaced by b.
 *
 * @pre size() < capacity() || contains(b.getID())
 * @post contains(b.getID()) && b == get(b.getID())
 */
void Catalog::add (Book b)
{
  //** To Be Implemented

  books.push_back(b);
}


/**
 * Check to see if a book is contained in the catalog.
 *
 * @param bookID the ID string of a potential book
 * @returns true iff a book with that ID is in the catalog.
 */
bool Catalog::contains(std::string bookID) const
{
//	for (int i = 0; i < theSize; ++i)
//	{
//		if (books[i].getID() == bookID)
//			return true;
//	}
//	return false;

	for (std::vector<Book>::size_type i = 0; i < books.size(); ++i)
	{
		if (books[i].getID() == bookID)
			return true;
	}
	return false;

}

/**
 * Return the book associated with a given ID.
 *
 * @param bookID the ID string of a potential book
 * @returns The book with that ID in the catalog, or
 *      Book() if the ID is unknown.
 */
Book Catalog::get(std::string bookID) const
{
  //** To Be Implemented

	for (std::vector<Book>::size_type i = 0; i < books.size(); ++i)
	{
		if (books[i].getID() == bookID)
			return books[i];
	}
	return Book();
}


/**
 * Return a book based upon ID ordering.
 *
 * @param i index of a desired book.
 * @return the requested book, or Book() if i is illegal.
 *
 * @pre 0 <= i && i < size()
 * @post if i0 <= i1, get(i0).getID() <= get(i1).getID()
 */
Book Catalog::get(int i) const
{
  //** To Be Implemented
    if(i >= 0 || i < books.size())
        return books[i];
    else
        return Book();
}



/**
 * Read a catalog from the input stream, terminating at
 * end of stream or at a book with ID "**END**".
 *
 * @param in the stream to read from.
 * @param catalog the catalog variable to hold the input.
 * @return the stream from which the data was read.
 */
std::istream& operator>> (std::istream& in, Catalog& catalog)
{
//	catalog = Catalog();
//	Book b;
//	while (in >> b)
//	{
//		if (b.getID() != "**END**")
//		{
//			if (catalog.capacity() <= catalog.size())
//			{
//				catalog.reserve (2*catalog.size() + 1);
//			}
//			catalog.add(b);
//		}
//		else
//		{
//			break;
//		}
//	}
//	return in;

	catalog = Catalog();
	Book b;
	while (in >> b)
	{
		if (b.getID() != "**END**")
		{
			catalog.add(b);
		}
		else
		{
			break;
		}
	}
	return in;


}

/**
 * Write a catalog to an output stream.
 *
 * @param out the stream to print to.
 * @param catalog the catalog to be printed.
 * @return the stream to which the data was written.
 *
 */
std::ostream& operator<< (std::ostream& out, const Catalog& catalog)
{
	for (int i = 0; i < catalog.size(); ++i)
	{
		out << catalog.get(i) << endl;
	}
	return out;
}

/**
 * Compare two catalogs.
 * @param left a catalog
 * @param right a catalog
 * @return True iff both catalogs are of the same length and all corresponding
 *    elements are equal.
 */
bool operator== (const Catalog& left, const Catalog& right)
{
//	if (left.size() != right.size())
//		return false;
//	else
//	{
//		for (int i = 0; i < left.size(); ++i)
//		{
//			if (!(left.get(i) == right.get(i)))
//				return false;
//		}
//		return true;
//	}
    return left == right;
}

/**
 * Compare two catalogs.
 * @param left a catalog
 * @param right a catalog
 * @return True iff left precedes right by lexicographical order.
 */
bool operator< (const Catalog& left, const Catalog& right)
{
//	int limit = min(left.size(), right.size());
//	for (int i = 0; i < limit; ++i)
//	{
//		Book b1 = left.get(i);
//		Book b2 = right.get(i);
//		if (b1 < b2)
//			return true;
//		else if (b2 < b1)
//			return false;
//	}
//	return left.size() < right.size();

    return left < right;

}







