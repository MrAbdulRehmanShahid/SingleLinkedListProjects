#include <iostream>
#include <limits>
using namespace std;

// Book Node
struct BookNode {
    int bookid;
    string title;
    BookNode* next;
};
//Gonna use linked list and apply its method and attributes on BookNode :/
class LinkedList {
private:
    int count;

    BookNode* GetNodeAt(int index) {
        BookNode* current = head;

        for (int g = 0; g < index && current != NULL; g++)
            current = current->next;

        return current;
    }

    void CopyBookData(BookNode* a, BookNode* b) {
        swap(a->bookid, b->bookid);
        swap(a->title, b->title);
    }

public:
    BookNode* head;

    // Constructor
    LinkedList() {
        head = NULL;
        count = 0;
    }

    // Return total number of books
    int Size() const {
        return count;
    }

    // Insert a book at the head
    void Insert(BookNode* book) {
        if (book == NULL)
            return;

        book->next = head;
        head = book;
        count++;
    }

    // Remove a book from the head
    BookNode* Remove() {
        if (IsEmpty())
            return NULL;

        BookNode* book = head;
        head = head->next;
        book->next = NULL;
        count--;

        return book;
    }

    bool IsEmpty() {
        return head == NULL;
    }

    bool IsNotEmpty() {
        return head != NULL;
    }

    // Insert at a specified index
    void InsertAt(BookNode* book, int index) {
        if (book == NULL)
            return;

        if (index < 0)
            index = 0;

        if (index > count)
            index = count;

        if (index == 0) {
            Insert(book);
            return;
        }

        BookNode* previous = GetNodeAt(index - 1);

        book->next = previous->next;
        previous->next = book;
        count++;
    }

    // Remove at a specified index
    BookNode* RemoveAt(int index) {
        if (IsEmpty())
            return NULL;

        if (index < 0)
            index = 0;

        if (index >= count)
            index = count - 1;

        if (index == 0)
            return Remove();

        BookNode* previous = GetNodeAt(index - 1);
        BookNode* book = previous->next;

        previous->next = book->next;
        book->next = NULL;
        count--;

        return book;
    }

    // Swap books at two indexes
    void Swap(int index1, int index2) {
        if (index1 < 0 || index1 >= count ||
            index2 < 0 || index2 >= count)
            return;

        if (index1 == index2)
            return;

        BookNode* first = GetNodeAt(index1);
        BookNode* second = GetNodeAt(index2);

        CopyBookData(first, second);
    }

    // Sort books by ID in ascending order
    void Sort() {
        for (BookNode* j = head; j != NULL; j = j->next) {
            for (BookNode* k = j->next; k != NULL; k = k->next) {
                if (j->bookid > k->bookid)
                    CopyBookData(j, k);
            }
        }
    }

    // Reverse the linked list
    void Reverse() {
        BookNode* previous = NULL;
        BookNode* current = head;
        BookNode* next = NULL;

        while (current != NULL) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    // Display all books
    void Print() {
        BookNode* current = head;
        int index = 0;

        cout << "\nIndex\tBook ID\tTitle\n";
        cout << "-------------------------------------------\n";

        while (current != NULL) {
            cout << index << "\t"
                 << current->bookid << "\t"
                 << current->title << endl;

            current = current->next;
            index++;
        }

        cout << "-------------------------------------------\n";
        cout << "Total books: " << count << endl;
    }

    // Copy constructor
    LinkedList(const LinkedList& other) {
        head = NULL;
        count = 0;

        BookNode* current = other.head;

        while (current != NULL) {
            BookNode* copy = new BookNode{
                current->bookid,
                current->title,
                NULL
            };

            InsertAt(copy, count);
            current = current->next;
        }
    }

    // Assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this == &other)
            return *this;

        while (!IsEmpty())
            delete Remove();

        BookNode* current = other.head;

        while (current != NULL) {
            BookNode* copy = new BookNode{
                current->bookid,
                current->title,
                NULL
            };

            InsertAt(copy, count);
            current = current->next;
        }

        return *this;
    }

    // Destructor
    ~LinkedList() {
        while (!IsEmpty())
            delete Remove();
    }
};

// Create a book node
BookNode* CreateBook(int id, string title) {
    BookNode* book = new BookNode;

    book->bookid = id;
    book->title = title;
    book->next = NULL;

    return book;
}

// Display menu
void DisplayMenu() {
    cout << "\n========================================\n";
    cout << "     LIBRARY BOOK COLLECTION SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Display All Books\n";
    cout << "2. Insert Book at Head\n";
    cout << "3. Remove Book from Head\n";
    cout << "4. Insert Book at Index\n";
    cout << "5. Remove Book at Index\n";
    cout << "6. Swap Books\n";
    cout << "7. Sort Books by ID\n";
    cout << "8. Reverse Book Collection\n";
    cout << "9. Check Collection Status\n";
    cout << "10. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

// Main function
int main() {
    LinkedList library;
    int choice;

    // Initial sample books
    library.InsertAt(CreateBook(103, "Operating System"), 0);
    library.InsertAt(CreateBook(101, "Data Structures"), 1);
    library.InsertAt(CreateBook(105, "Computer Networks"), 2);
    library.InsertAt(CreateBook(102, "Database Systems"), 3);
    library.InsertAt(CreateBook(104, "Software Engineering"), 4);

    do {
        DisplayMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Enter a number from 1 to 10.\n";
            continue;
        }

        switch (choice) {

        case 1: {
            // Display all books
            library.Print();
            break;
        }

        case 2: {
            // Insert at head
            int id;
            string title;

            cout << "Enter Book ID: ";
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Book ID!\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Book Title: ";
            getline(cin, title);

            library.Insert(CreateBook(id, title));

            cout << "Book inserted at head successfully!\n";
            break;
        }

        case 3: {
            // Remove from head
            BookNode* removed = library.Remove();

            if (removed != NULL) {
                cout << "Removed Book: "
                     << removed->bookid << " - "
                     << removed->title << endl;

                delete removed;
            } else {
                cout << "Collection is empty. No book to remove.\n";
            }

            break;
        }

        case 4: {
            // Insert at index
            int id, index;
            string title;

            cout << "Enter Book ID: ";
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Book ID!\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Book Title: ";
            getline(cin, title);

            cout << "Enter index (0 to " << library.Size() << "): ";

            if (!(cin >> index)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index!\n";
                break;
            }

            if (index < 0 || index > library.Size()) {
                cout << "Invalid index! Book was not inserted.\n";
                break;
            }

            library.InsertAt(CreateBook(id, title), index);

            cout << "Book inserted successfully at index "
                 << index << ".\n";
            break;
        }

        case 5: {
            // Remove at index
            int index;

            if (library.IsEmpty()) {
                cout << "Collection is empty. No book to remove.\n";
                break;
            }

            cout << "Enter index (0 to "
                 << library.Size() - 1 << "): ";

            if (!(cin >> index)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index!\n";
                break;
            }

            if (index < 0 || index >= library.Size()) {
                cout << "Invalid index! No book was removed.\n";
                break;
            }

            BookNode* removed = library.RemoveAt(index);

            if (removed != NULL) {
                cout << "Removed Book: "
                     << removed->bookid << " - "
                     << removed->title << endl;

                delete removed;
            }

            break;
        }

        case 6: {
            // Swap two books
            int index1, index2;

            if (library.Size() < 2) {
                cout << "At least two books are required to swap.\n";
                break;
            }

            cout << "Enter first index (0 to "
                 << library.Size() - 1 << "): ";

            if (!(cin >> index1)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index!\n";
                break;
            }

            cout << "Enter second index (0 to "
                 << library.Size() - 1 << "): ";

            if (!(cin >> index2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index!\n";
                break;
            }

            if (index1 < 0 || index1 >= library.Size() ||
                index2 < 0 || index2 >= library.Size()) {
                cout << "Invalid index! Books were not swapped.\n";
                break;
            }

            library.Swap(index1, index2);

            cout << "Books swapped successfully!\n";
            break;
        }

        case 7: {
            // Sort by ID
            library.Sort();
            cout << "Books sorted by ID in ascending order.\n";
            library.Print();
            break;
        }

        case 8: {
            // Reverse collection
            library.Reverse();
            cout << "Book collection reversed successfully.\n";
            library.Print();
            break;
        }

        case 9: {
            // Check collection status
            if (library.IsEmpty()) {
                cout << "Collection Status: EMPTY\n";
            } else {
                cout << "Collection Status: NOT EMPTY\n";
                cout << "Total books in collection: "
                     << library.Size() << endl;
            }

            break;
        }

        case 10: {
            cout << "Exiting Library Book Collection System.\n";
            cout << "Thank you!\n";
            break;
        }

        default: {
            cout << "Invalid choice! Please select 1 to 10.\n";
        }

        }

    } while (choice != 10);

    return 0;
}

