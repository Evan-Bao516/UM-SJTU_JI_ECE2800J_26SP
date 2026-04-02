#include <iostream>
#include <string>
#include "h4.h"

bookInventory::bookInventory() {
  for (int i = 0; i < MAX_BOOKS; ++i) {
    books[i] = Book();
  }
}

void bookInventory::addBook(const Book &book) {
  if (numBooks == MAX_BOOKS) {
    throw Exception("The inventory is full.");
  }
  books[numBooks] = book;
  ++numBooks;
}

int bookInventory::searchBook(const std::string &title) const {
  for (unsigned int i = 0; i < numBooks; ++i) {
    if (books[i].title == title) {
      return static_cast<int>(i + 1);
    }
  }
  throw Exception("Book " + title + " not found.");
}

void bookInventory::setBook(const Book &book, int ID) {
  if (ID < 1 || ID > MAX_BOOKS) {
    throw Exception("Invalid book ID.");
  }
  if (ID <= static_cast<int>(numBooks)) {
    books[ID - 1] = book;
  } else {
    books[numBooks] = book;
    ++numBooks;
  }
}

Book bookInventory::viewBook(int ID) const {
  if (ID < 1 || ID > static_cast<int>(numBooks)) {
    throw Exception("Invalid book ID.");
  }
  return books[ID - 1];
}

void bookInventory::removeBook(int ID) {
  if (ID < 1 || ID > static_cast<int>(numBooks)) {
    throw Exception("Invalid book ID.");
  }
  for (unsigned int i = static_cast<unsigned int>(ID - 1); i < numBooks - 1;
       ++i) {
    books[i] = books[i + 1];
  }
  books[numBooks - 1] = Book();
  --numBooks;
}

void bookInventory::printInventory() const {
  if (numBooks == 0) {
    throw Exception("The inventory is empty.");
  }
  for (unsigned int i = 0; i < numBooks; ++i) {
    std::cout << "Book ID: " << (i + 1) << "\n";
    std::cout << "Title: " << books[i].title << "\n";
    std::cout << "Author: " << books[i].author << "\n";
    std::cout << "Status: "
              << (books[i].isAvailable ? "available" : "not available") << "\n";
  }
}

library::library() {}

void library::borrowBook(int ID) {
  if (ID < 1 || ID > static_cast<int>(numBooks)) {
    throw Exception("Invalid book ID.");
  }
  if (!books[ID - 1].isAvailable) {
    throw Exception("Book " + books[ID - 1].title + " is not available.");
  }
  books[ID - 1].isAvailable = false;
}

void library::returnBook(int ID) {
  if (ID < 1 || ID > static_cast<int>(numBooks)) {
    throw Exception("Invalid book ID.");
  }
  if (books[ID - 1].isAvailable) {
    throw Exception("Book " + books[ID - 1].title + " is already available.");
  }
  books[ID - 1].isAvailable = true;
}

void library::listBorrowed() const {
  bool found = false;
  for (unsigned int i = 0; i < numBooks; ++i) {
    if (!books[i].isAvailable) {
      std::cout << "Book ID: " << (i + 1) << "\n";
      std::cout << "Title: " << books[i].title << "\n";
      std::cout << "Author: " << books[i].author << "\n";
      found = true;
    }
  }
  if (!found) {
    throw Exception("All books are available.");
  }
}
