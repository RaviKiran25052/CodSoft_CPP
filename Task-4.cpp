#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

#define MAX_BOOKS 5
#define MAX_ALLOWED_BOOKS 2
#define FINE_RATE 1
#define SECONDS_PER_DAY 24 * 60 * 60
#define DAYS_ALLOWED 7

struct Book {
    string title;
    string author;
    string ISBN;
    bool issued;
    time_t issueDate;
    int fine;
};

time_t convertToDate(const string& date) {
    struct tm tm = {0};
    stringstream ss(date);
    ss >> get_time(&tm, "%d-%m-%Y");
    return mktime(&tm);
}

int calculateFine(time_t issueDate, time_t returnDate) {

    double diffSeconds = difftime(returnDate, issueDate);
    int diffDays = static_cast<int>(diffSeconds / SECONDS_PER_DAY);

    if (diffDays <= DAYS_ALLOWED) {
        return 0;
    } else {
        int extraDays = diffDays - DAYS_ALLOWED;
        return extraDays * FINE_RATE;
    }
}

void borrowBook(Book* books, int* numIssued) {
    if (*numIssued >= MAX_ALLOWED_BOOKS) {
        cout << "You have already borrowed the maximum number of books (" << MAX_ALLOWED_BOOKS << ")." << endl;
        return;
    }

    cout << "\nEnter the ISBN of the book to borrow: ";
    string ISBN;
    cin >> ISBN;

    cout << "Enter the issue date (dd-mm-yyyy): ";
    string issueDateStr;
    cin >> issueDateStr;

    time_t issueDate = convertToDate(issueDateStr);

    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (!books[i].issued && books[i].ISBN == ISBN) {
            books[i].issued = true;
            books[i].issueDate = issueDate;
            books[i].fine = 0;
            (*numIssued)++;
            cout << "\nBook with ISBN '" << ISBN << "' has been borrowed." << endl;
            return;
        }
    }

    cout << "Book not found or already issued." << endl;
}

void returnBook(Book* books, int* numIssued) {
    if (*numIssued == 0) {
        cout << "No books are currently issued." << endl;
        return;
    }

    cout << "\nBooks currently issued: " << endl;
    bool issuedBooksExist = false;

    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (books[i].issued) {
            cout << "\n  ISBN: " << books[i].ISBN << "\n  Title: " << books[i].title << "\n  Author: " << books[i].author << "\n  Issued Date: " << put_time(localtime(&books[i].issueDate), "%d-%m-%Y") << endl;
            issuedBooksExist = true;
        }
    }

    if (!issuedBooksExist) {
        cout << "No books are currently issued." << endl;
        return;
    }

    cout << "\nEnter the ISBN of the book to return: ";
    string ISBN;
    cin >> ISBN;

    time_t currentDate = time(nullptr);

    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (books[i].issued && books[i].ISBN == ISBN) {
            time_t issueDate = books[i].issueDate;
            int fine = calculateFine(issueDate, currentDate);
            books[i].fine += fine;

            books[i].issued = false;
            (*numIssued)--;
            
            cout << "\nBook '" << books[i].title << "' has been returned." << endl;
            cout << "Fine: " << fine << " rupees." << endl;
            return;
        }
    }

    cout << "Book not found or already returned." << endl;
}

void displayIssuedBooks(const Book* books) {
    cout << "\nIssued Books: ";
    bool found = false;
    int totalFine = 0;

    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (books[i].issued) {
            cout << "\n\n  ISBN: " << books[i].ISBN << "\n  Title: " << books[i].title << "\n  Author: " << books[i].author << "\n  Issued Date: " << put_time(localtime(&books[i].issueDate), "%d-%m-%Y") << endl;
            found = true;
        }

        if (books[i].fine > 0) {
            totalFine += books[i].fine;
        }
    }

    if (!found) {
        cout << "No books are currently issued.";
    }

    cout << "\nTotal Fine for all books: " << totalFine << " rupees" << endl;
}

void displayAvailableBooks(const Book* books) {
    cout << "\nAvailable Books:" << endl;
    bool found = false;
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (!books[i].issued) {
            cout << "\n  ISBN: " << books[i].ISBN << "\n  Title: " << books[i].title << "\n  Author: " << books[i].author << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No books are available." << endl;
    }
}

int main() {
    Book books[MAX_BOOKS] = {
        {"The Great Gatsby", "F. Scott Fitzgerald", "100", false, 0, 0},
        {"To Kill a Mockingbird", "Harper Lee", "101", false, 0, 0},
        {"1984", "George Orwell", "102", false, 0, 0},
        {"Brave New World", "Aldous Huxley", "103", false, 0, 0},
        {"The Catcher in the Rye", "J.D. Salinger", "104", false, 0, 0}
	};
    int numIssued = 0;

    int choice;
    do {
        cout << "\n--------------------------------------------------------" << endl;
        cout << "\n1. Borrow a Book\n2. Return a Book\n3. Display Issued Books\n4. Display Available Books\n5. Quit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAvailableBooks(books);
                borrowBook(books, &numIssued);
                break;
            case 2:
                returnBook(books, &numIssued);
                break;
            case 3:
                displayIssuedBooks(books);
                break;
            case 4:
                displayAvailableBooks(books);
                break;
            case 5:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 5);

    return 0;
}

