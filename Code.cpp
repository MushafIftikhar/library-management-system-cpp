#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Base class Book
class Book {
protected:
    string title;
    string author;
    string genre;
    int isbn;
    bool isBorrowed;
    float rating;
    static int isbnCounter;
public:
    // Static member variable initialization
    // Constructor
    Book(string t, string a, string g) : title(t), author(a), genre(g) {
        // Generate a random ISBN between 1000 and 9999
        isbn = rand() % 9000 + 1000;
        // Generate a random rating between 0 and 5
        rating = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 5.0);
    }

    // Getters and setters for ISBN and borrowed status
    int getISBN() const { return isbn; }
    bool getBorrowedStatus() const { return isBorrowed; }
    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    // Display book details
    virtual void displayDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Genre: " << genre << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
        cout << "Rating: " << rating << endl;
    }
};

int Book::isbnCounter = 0; // Initializing static member variable

// Derived class FictionBook inherits from Book
class FictionBook : public Book {
public:
    // Constructor
    FictionBook(string t, string a, string g) : Book(t, a, g) {}

    // Display book details
    void displayDetails() override {
        cout << "Fiction Book Details:" << endl;
        Book::displayDetails();
        cout << endl;
    }
};

// Derived class NonFictionBook inherits from Book
class NonFictionBook : public Book {
public:
    // Constructor
    NonFictionBook(string t, string a, string g) : Book(t, a, g) {}

    // Display book details
    void displayDetails() override {
        cout << "Non-Fiction Book Details:" << endl;
        Book::displayDetails();
        cout << endl;
    }
};

// Library class to manage books
class Library {
private:
    Book* books[100];
    int numBooks;

public:
    // Constructor
    Library() : numBooks(0) {}

    // Add a book to the library
    void addBook(Book* book) {
        books[numBooks++] = book;
    }

    // Borrow a book from the library
    void borrowBook(int isbn) {
        for (int i = 0; i < numBooks; i++) {
            if (books[i]->getISBN() == isbn) {
                if (!books[i]->getBorrowedStatus()) {
                    books[i]->borrowBook();
                    cout << "Book borrowed successfully!" << endl;
                } else {
                    char choice;
                    cout << "This book is already borrowed. Do you still want to borrow it? (y/n): ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        books[i]->borrowBook();
                        cout << "Book borrowed successfully!" << endl;
                    } else {
                        cout << "Borrow canceled." << endl;
                    }
                }
                return;
            }
        }
        cout << "Book not found!"<< endl;
    }

    // Return a book to the library
    void returnBook(int isbn) {
        for (int i = 0; i < numBooks; i++) {
            if (books[i]->getISBN() == isbn) {
                if (books[i]->getBorrowedStatus()) {
                    char choice;
                    cout << "Are you sure you want to return this book? (y/n): ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        books[i]->returnBook();
                        cout << "Book returned successfully!" << endl;
                    } else {
                        cout << "Return canceled." << endl;
                    }
                } else {
                    cout << "Book not borrowed!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Display all books in the library
    void displayBooks() {
        for (int i = 0; i < numBooks; i++) {
            books[i]->displayDetails();
        }
    }
};

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create a library
    Library lib;

    // Prompt user to add books to the library
    cout << "Welcome to the Library Management System!" << endl;
    cout << "Let's add some books to the library." << endl;
    char addMore;
    do {
        string title, author, genre, fictionInput;
        cout << "Enter the title of the book: ";
        getline(cin, title);
        cout << "Enter the author of the book: ";
        getline(cin, author);
        cout << "Enter the genre of the book: ";
        getline(cin, genre);
        cout << "Is this book fiction or non-fiction? (Enter 'fiction' or 'non-fiction'): ";
        getline(cin, fictionInput);

        // Add book to the library based on user input
        if (fictionInput == "fiction") {
            lib.addBook(new FictionBook(title, author, genre));
        } else if (fictionInput == "non-fiction") {
            lib.addBook(new NonFictionBook(title, author, genre));
        } else {
            cout << "Invalid input. Book not added to the library." << endl;
        }

        cout << "Do you want to add another book? (y/n): ";
        cin >> addMore;
        cin.ignore(); // Clear the newline character from the input buffer
    } while (addMore == 'y' || addMore == 'Y');

    // Display all books in the library
    cout << endl;
    cout << "All Books in the Library:" << endl;
    lib.displayBooks();

    // Borrow a book
    int isbnToBorrow;
    cout << "Enter the ISBN of the book you want to borrow: ";
    cin >> isbnToBorrow;
    lib.borrowBook(isbnToBorrow);

    // Return a book
    int isbnToReturn;
    cout << "Enter the ISBN of the book you want to return: ";
    cin >> isbnToReturn;
    lib.returnBook(isbnToReturn);

    // Display all books in the library after actions
    cout << endl;
    cout << "All Books in the Library after borrowing and returning:" << endl;
    lib.displayBooks();

    return 0;
}