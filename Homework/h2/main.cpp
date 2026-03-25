#include <iostream>
#include <string>
#include "h2.h"

int main() {
    try {
        Library lib = initLibrary();
        std::string command;
        std::string dummy;

        while (std::cin >> command) {
            if (command == "ADD") {
                std::string title;
                std::string author;
                std::getline(std::cin, dummy);

                if (std::getline(std::cin, title) && std::getline(std::cin, author)) {
                    addBook(lib, title, author);
                }
            } else if (command == "BORROW") {
                int bookID = 0;

                if (std::cin >> bookID) {
                    borrowBook(lib, bookID);
                } else {
                    std::cin.clear();
                    std::getline(std::cin, dummy);
                }
            } else if (command == "RETURN") {
                int bookID = 0;

                if (std::cin >> bookID) {
                    returnBook(lib, bookID);
                } else {
                    std::cin.clear();
                    std::getline(std::cin, dummy);
                }
            } else if (command == "PRINT") {
                printLibrary(lib);
            }
        }
    }

    catch (...) {
        return 1;
    }

    return 0;
}
