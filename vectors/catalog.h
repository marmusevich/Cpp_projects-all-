/*
 * catalog.h
 *
 *  Created on: Apr 10, 2017
 *      Author: zeil
 */

#ifndef CATALOG_H_
#define CATALOG_H_

#include <string>
#include <iostream>
#include <vector>

#include "book.h"

/**
 * A list of books, identified by Gutenberg ID.
 */
class Catalog {
public:
	/**
	 * Create a new empty catalog, capable of holding up to
	 * maxCapacity books.
	 *
	 * @param maxCapacity maximum number of books this catalog
	 *    can hold before needing to allocate extra storage.
	 */
	Catalog (int maxCapacity = 100);

	/**
	 * How many books currently in this catalog?
	 *
	 * @return number of books in the catalog.
	 */
	int size() const;

	/**
	 * How many books can this catalog hold before needing
	 * to allocate extra storage?
	 *
	 * @return capacity of this catalog.
	 */
	int capacity() const;

	/**
	 * Attempt to alter the capacity of this catalog so that
	 * it can hold at least newCapcity books.  Existing books
	 * in the catalog are retained.
	 *
	 * @param newCapacity maximum number of books we would like to be able
	 *    to store in this catalog.
	 * @post capacity() >= newCapacity
	 */
	void reserve (int newCapacity);

	/**
	 * Add a book to the catalog. If a book with the same ID exists, it is
	 * replaced by b. If a book with that ID is not already in he catalog,
     * then the catalog size is increased by 1.
	 *
	 * @post contains(b.getID()) && b == get(b.getID()) && capacity() >= size()
	 */
	void add (Book b);


	/**
	 * Check to see if a book is contained in the catalog.
	 *
	 * @param bookID the ID string of a potential book
	 * @returns true iff a book with that ID is in the catalog.
	 */
	bool contains(std::string bookID) const;

	/**
	 * Return the book associated with a given ID.
	 *
	 * @param bookID the ID string of a potential book
	 * @returns The book with that ID in the catalog, or
	 *      Book() if the ID is unknown.
	 */
	Book get(std::string bookID) const;

	/**
	 * Return a book based upon ID ordering.
	 *
	 * @param i index of a desired book.
	 * @return the requested book, or Book() if i is illegal.
	 *
	 * @pre 0 <= i && i < size()
	 * @post if i0 <= i1, get(i0).getID() <= get(i1).getID()
	 */
	Book get(int i) const;

private:
  std::vector<Book> books;
};


/**
 * Read a catalog from the input stream, terminating at
 * end of stream or at a book with ID "**END**".
 *
 * @param in the stream to read from.
 * @param catalog the catalog variable to hold the input.
 * @return the stream from which the data was read.
 */
std::istream& operator>> (std::istream& in, Catalog& catalog);

/**
 * Write a catalog to an output stream.
 *
 * @param out the stream to print to.
 * @param catalog the catalog to be printed.
 * @return the stream to which the data was written.
 *
 */
std::ostream& operator<< (std::ostream& out, const Catalog& catalog);

/**
 * Compare two catalogs.
 * @param left a catalog
 * @param right a catalog
 * @return True iff both catalogs are of the same length and all corresponding
 *    elements are equal.
 */
bool operator== (const Catalog& left, const Catalog& right);

/**
 * Compare two catalogs.
 * @param left a catalog
 * @param right a catalog
 * @return True iff left precedes right by lexicographical order.
 */
bool operator< (const Catalog& left, const Catalog& right);







#endif /* CATALOG_H_ */
