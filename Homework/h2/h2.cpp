#include <iostream>
#include <string>
#include "h2.h"

Library initLibrary() {
    Library lib;
    lib.numBooks = 0;
    return lib;
}

void addBook(Library &lib, const std::string &title,
             const std::string &author) {
    if (lib.numBooks >= MAX_BOOKS) {
        std::cout << "The library is full.\n";
        return;
    }
    lib.books[lib.numBooks].title = title;
    lib.books[lib.numBooks].author = author;
    lib.books[lib.numBooks].isAvailable = true;
    lib.books[lib.numBooks].ID = lib.numBooks + 1;
    lib.numBooks++;
}

void borrowBook(Library &lib, int ID) {
    if (ID < 1 || ID > lib.numBooks) {
        std::cout << "Invalid book ID.\n";
        return;
    }
    if (lib.books[ID - 1].isAvailable) {
        lib.books[ID - 1].isAvailable = false;
        std::cout << "Book " << lib.books[ID - 1].title << " is borrowed.\n";
    } else {
        std::cout << "Book " << lib.books[ID - 1].title << " is not available.\n";
    }
}

void returnBook(Library &lib, int ID) {
    if (ID < 1 || ID > lib.numBooks) {
        std::cout << "Invalid book ID.\n";
        return;
    }
    if (!lib.books[ID - 1].isAvailable) {
        lib.books[ID - 1].isAvailable = true;
        std::cout << "Book " << lib.books[ID - 1].title << " is returned.\n";
    } else {
        std::cout << "Book " << lib.books[ID - 1].title << " is already available.\n";
    }
}

void printLibrary(const Library &lib) {
    if (lib.numBooks == 0) {
        std::cout << "The library is empty.\n";
        return;
    }
    for (int iii = 0; iii < lib.numBooks; ++iii) {
        std::cout << "Book ID: " << lib.books[iii].ID << "\n";
        std::cout << "Title: " << lib.books[iii].title << "\n";
        std::cout << "Author: " << lib.books[iii].author << "\n";
        std::cout << "Status: " << (lib.books[iii].isAvailable ? "available" : "not available") << "\n";
    }
}
