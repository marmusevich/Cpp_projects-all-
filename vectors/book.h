#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>


class Book {
private:
  std::string title;
  std::string id;
  std::string authorName;
public:

  /**
   * Create a default book.
   *
   * @post getID() == "" && getTitle() == "" && getAuthor() == ""
   */
  Book() {}

  /**
   * Create a book.
   *
   * @param id the Gutenberg ID for this book
   * @param authorInfo the author of the book
   * @param title the title of the book
   */
  Book (std::string id, std::string authorInfo, std::string title);


  /**
   * The Gutenberg project ID for this book
   */
  std::string getID() const  {return id;}
  void setID (std::string ID) {id = ID;}

  /**
   *  Title of this book
   */
  std::string getTitle() const {return title;}
  void setTitle (std::string theTitle)  {title = theTitle;}

  /**
   * Name of the book's author(s)
   */
  std::string getAuthor() const  {return authorName;}
  void setAuthor (std::string name) {authorName = name;}

  /**
   *  Ordered by ID
   */
  bool operator< (const Book&) const;
  bool operator== (const Book&) const;
};

// Print a book as id, tab, author, tab, title
std::ostream& operator<< (std::ostream& out, const Book& b);


// Read a book. Input format is id, then author, then title, 
// all on one line, separated by tab characters.
std::istream& operator>> (std::istream& in, Book& b);

#endif
