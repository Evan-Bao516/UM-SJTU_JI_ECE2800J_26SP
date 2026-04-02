#ifndef H4_H
#define H4_H

#include <string>

const int MAX_BOOKS = 10;

class Exception {
  std::string message;

 public:
  explicit Exception(const std::string &message) : message(message) {}
  const std::string &what() const { return message; }
};

struct Book {
  std::string title;
  std::string author;
  bool isAvailable;

  // Default constructor
  Book() : isAvailable(true) {}
  // Constructor with parameters
  Book(const std::string &title, const std::string &author)
      : title(title), author(author), isAvailable(true) {}
};

class bookInventory {
 protected:
  // Array of books
  Book books[MAX_BOOKS];
  // Number of books in the inventory
  unsigned int numBooks{0};

 public:
  /**
   * @brief Default constructor. Initializes `numBooks` to 0 and fills
   * the `books` array with default-constructed `Book` objects.
   */
  bookInventory();

  /**
   * @brief Returns the number of books in the inventory.
   *
   * @return The number of books.
   */
  int getNumBooks() const { return static_cast<int>(numBooks); }

  /**
   * @brief Adds a book to the inventory.
   *
   * @param book The book to be added.
   * @throw Exception if the inventory is full.
   */
  virtual void addBook(const Book &book);

  /**
   * @brief Searches for a book in the inventory.
   *
   * @param title The title of the book to be searched.
   * @return The ID of the book in the inventory. The ID is the index of the
   * book in the books array + 1.
   * @throw Exception if the book is not found.
   */
  virtual int searchBook(const std::string &title) const;

  /**
   * @brief Updates a book in the inventory. If the slot at the given ID is
   * occupied, replaces the existing book. If the ID is within bounds but
   * the slot is unoccupied, appends the book to the next available position
   * and increments `numBooks`.
   *
   * @param book The book to be set.
   * @param ID The ID of the book to be set. The ID is the index of the book in
   * the books array + 1.
   * @throw Exception if the ID is invalid (ID < 1 or ID > MAX_BOOKS).
   */
  virtual void setBook(const Book &book, int ID);

  /**
   * @brief Returns the book at the given ID without modifying the inventory.
   *
   * @param ID The ID of the book. The ID is the index of the book in the books
   * array + 1.
   * @return The book at the given ID.
   * @throw Exception if the ID is invalid (ID < 1 or ID > numBooks).
   */
  virtual Book viewBook(int ID) const;

  /**
   * @brief Removes a book from the inventory.
   *
   * @param ID The ID of the book to be removed. The ID is the index of the book
   * in the books array + 1.
   * @throw Exception if the ID is invalid (ID < 1 or ID > numBooks).
   */
  virtual void removeBook(int ID);

  /**
   * @brief Prints the inventory of books.
   *
   * @throw Exception if the inventory is empty.
   */
  virtual void printInventory() const;

  bookInventory(const bookInventory &) = default;
  bookInventory &operator=(const bookInventory &) = default;
  bookInventory(bookInventory &&) = default;
  bookInventory &operator=(bookInventory &&) = default;
  virtual ~bookInventory() = default;
};

class library : public bookInventory {
 public:
  /**
   * @brief Default constructor. Same as the default constructor of
   * `bookInventory`: initializes `numBooks` to 0 and fills the `books`
   * array with default-constructed `Book` objects.
   */
  library();

  /**
   * @brief Borrows a book from the library.
   *
   * @param ID The ID of the book to be borrowed. The ID is the index of the
   * book in the books array + 1.
   * @throw Exception if the ID is invalid (ID < 1 or ID > numBooks).
   * @throw Exception if the book is not available.
   */
  void borrowBook(int ID);

  /**
   * @brief Returns a book to the library.
   *
   * @param ID The ID of the book to be returned. The ID is the index of the
   * book in the books array + 1.
   * @throw Exception if the ID is invalid (ID < 1 or ID > numBooks).
   * @throw Exception if the book is already available.
   */
  void returnBook(int ID);

  /**
   * @brief Prints the books that are currently borrowed.
   *
   * @throw Exception if there are no borrowed books.
   */
  void listBorrowed() const;

  library(const library &) = default;
  library &operator=(const library &) = default;
  library(library &&) = default;
  library &operator=(library &&) = default;
  ~library() override = default;
};

#endif
