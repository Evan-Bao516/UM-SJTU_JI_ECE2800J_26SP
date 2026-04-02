#include <iostream>
#include <string>
#include "h4.h"

using std::cin;
using std::cout;
using std::string;
using std::ws;

int main() {
  try {
    library lib;
    string line;
    while (cin >> line) {
      try {
        if (line == "ADD") {
          string title;
          string author;
          cin >> ws;
          getline(cin, title);
          getline(cin, author);
          lib.addBook(Book(title, author));
        } else if (line == "REMOVE") {
          int iidd = 0;
          cin >> iidd;
          lib.removeBook(iidd);
        } else if (line == "SEARCH") {
          string title;
          cin >> ws;
          getline(cin, title);
          const int iidd = lib.searchBook(title);
          cout << "Book ID: " << iidd << "\n";
        } else if (line == "SET") {
          int iidd = 0;
          cin >> iidd;
          string title;
          string author;
          cin >> ws;
          getline(cin, title);
          getline(cin, author);
          lib.setBook(Book(title, author), iidd);
        } else if (line == "GET_NUM") {
          cout << lib.getNumBooks() << "\n";
        } else if (line == "VIEW") {
          int iidd = 0;
          cin >> iidd;
          const Book book = lib.viewBook(iidd);
          cout << "Book ID: " << iidd << "\n";
          cout << "Title: " << book.title << "\n";
          cout << "Author: " << book.author << "\n";
          cout << "Status: " << (book.isAvailable ? "available" : "not available")
               << "\n";
        } else if (line == "BORROW") {
          int iidd = 0;
          cin >> iidd;
          const Book book = lib.viewBook(iidd);
          lib.borrowBook(iidd);
          cout << "Book " << book.title << " is borrowed.\n";
        } else if (line == "RETURN") {
          int iidd = 0;
          cin >> iidd;
          const Book book = lib.viewBook(iidd);
          lib.returnBook(iidd);
          cout << "Book " << book.title << " is returned.\n";
        } else if (line == "LIST_BORROWED") {
          lib.listBorrowed();
        } else if (line == "PRINT") {
          lib.printInventory();
        }
      } catch (const Exception &e) {
        cout << e.what() << "\n";
      }
    }
  } catch (...) {
    return 1;
  }
  return 0;
}
