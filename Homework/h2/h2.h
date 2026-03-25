#ifndef H2_H
#define H2_H

#include <string>

constexpr int MAX_BOOKS = 10;

struct Book {
    int ID = 0;  // An int representing the book's unique identifier,
                 // used to track and manage books within the library. The ID of the first book added is 1.
    std::string title;  // A std::string representing the book's title.
    std::string author;  // A std::string representing the book's author.
    bool isAvailable = false;  // A bool indicating whether the book is available for borrowing.
                               // It is true if available and false if borrowed.
};

struct Library {
    Book books[MAX_BOOKS];  // A fixed-size array of Book of size MAX_BOOKS.
    int numBooks = 0;  // An int representing the number of books currently in the library.
};

Library initLibrary();
// Effects: Returns a Library with no books (i.e., numBooks is 0).

void addBook(Library &lib, const std::string &title, const std::string &author);
// Modifies: lib
/* Effects: If lib is full, prints "The library is full." followed by a newline and does nothing else.
Otherwise, appends a new book to lib with the given title and author , isAvailable set to
true, and ID set to numBooks + 1 ; then increments numBooks. */

void borrowBook(Library &lib, int ID);
// Modifies: lib (only if ID is valid and the book is available)
/* Effects: If ID is not a valid book ID, prints "Invalid book ID." followed by a newline. Otherwise, if
the book is available, sets its availability to false and prints "Book <title> is borrowed."
followed by a newline; if the book is not available, prints "Book <title> is not available."
followed by a newline. */
// Sample Output: Book The Catcher in the Rye is borrowed.

void returnBook(Library &lib, int ID);
// Modifies: lib (only if ID is valid and the book is not available)
/* Effects: If ID is not a valid book ID, prints "Invalid book ID." followed by a newline. Otherwise, if
the book is not available, sets its availability to true and prints "Book <title> is returned."
followed by a newline; if the book is already available, prints "Book <title> is already
available." followed by a newline. */
// Sample Output: Book 1984 is already available.

void printLibrary(const Library &lib);
/* Effects: If lib is empty, prints "The library is empty." followed by a newline. Otherwise, for
each book in lib , prints the following four lines in order:
1 | Book ID: <ID>
2 | Title: <title>
3 | Author: <author>
4 | Status: <available|not available> */

#endif  // H2_H
