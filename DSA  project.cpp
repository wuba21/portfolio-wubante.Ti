// simple book wishlist system in C++ using arrays and linked lists.
#include <iostream>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

struct Book
{
    string title;
    string author;
    int year;
};
Book *bookArray = nullptr;
int bookCount = 0;

void inputBooks()
{
    cout << "\n\t WELCOME TO THE SIMPLE BOOK WISHLIST SYSTEM:\n\n";
    cout << "  Enter number of books in your wishlist: ";
    cin >> bookCount;
    cin.ignore();

    if (bookCount <= 0)
    {
        cout << "Invalid number.\n";
        bookCount = 0;
        return;
    }

    bookArray = new Book[bookCount];

    cout << "Enter book details:\n";
    for (int i = 0; i < bookCount; ++i)
    {
        cout << "\nBook " << (i + 1) << " Title: ";
        getline(cin, bookArray[i].title);
        cout << "Author: ";
        getline(cin, bookArray[i].author);
        cout << "Year: ";
        cin >> bookArray[i].year;
        cin.ignore();
    }
}

void displayBookArray()
{
    if (bookCount == 0)
    {
        cout << "No books in array.\n";
        return;
    }
    cout << "\nBook List (Array):\n";
    for (int i = 0; i < bookCount; ++i)
    {
        cout << i + 1 << ". " << bookArray[i].title << "   "
             << bookArray[i].author << "  " << bookArray[i].year << endl;
    }
}

void sortBooks()
{
    for (int i = 0; i < bookCount - 1; ++i)
    {
        for (int j = 0; j < bookCount - i - 1; ++j)
        {
            if (bookArray[j].title > bookArray[j + 1].title)
            {
                swap(bookArray[j], bookArray[j + 1]);
            }
        }
    }
}

int linearSearch(string searchTitle)
{
    for (int i = 0; i < bookCount; ++i)
    {
        if (bookArray[i].title == searchTitle)
        {
            return i;
        }
    }
    return -1;
}

int binarySearch(string searchTitle)
{
    int left = 0, right = bookCount - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (bookArray[mid].title == searchTitle)
            return mid;
        else if (bookArray[mid].title < searchTitle)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
struct Node
{
    Book data;
    string insertTime;
    Node *next;
};

string getCurrentTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void insertEnd(Node *&head, Book b, bool showMessage = true)
{
    Node *newNode = new Node{b, getCurrentTime(), NULL};
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
    if (showMessage)
        cout << "The book has been added at the end at " << newNode->insertTime << ".\n";
}

void insertAtBeginning(Node *&head, Book b)
{
    Node *newNode = new Node{b, getCurrentTime(), head};
    head = newNode;
    cout << "The book has been added at the beginning at " << newNode->insertTime << ".\n";
}

bool insertAfterTitle(Node *head, string targetTitle, Book b)
{
    Node *current = head;
    while (current != NULL && current->data.title != targetTitle)
    {
        current = current->next;
    }
    if (current == NULL)
        return false;

    Node *newNode = new Node{b, getCurrentTime(), current->next};
    current->next = newNode;
    cout << "The book has been added after '" << targetTitle << "' at " << newNode->insertTime << ".\n";
    return true;
}

bool deleteFromBeginning(Node *&head)
{
    if (head == NULL)
        return false;
    Node *temp = head;
    head = head->next;
    delete temp;
    return true;
}

bool deleteFromEnd(Node *&head)
{
    if (head == NULL)
        return false;
    if (head->next == NULL)
    {
        delete head;
        head = NULL;
        return true;
    }
    Node *current = head;
    while (current->next->next != NULL)
        current = current->next;
    delete current->next;
    current->next = NULL;
    return true;
}

bool deleteByTitle(Node *&head, string targetTitle)
{
    if (head == NULL)
        return false;
    if (head->data.title == targetTitle)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    Node *current = head;
    while (current->next != NULL && current->next->data.title != targetTitle)
    {
        current = current->next;
    }
    if (current->next == NULL)
        return false;
    Node *temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

bool deleteFromMiddle(Node *&head, int pos)
{
    if (head == NULL || pos < 1)
        return false;
    if (pos == 1)
        return deleteFromBeginning(head);

    Node *current = head;
    for (int i = 1; current != NULL && i < pos - 1; i++)
    {
        current = current->next;
    }
    if (current == NULL || current->next == NULL)
        return false;

    Node *temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

bool updateBookInfo(Node *head, string targetTitle)
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->data.title == targetTitle)
        {
            cout << "Enter new title: ";
            getline(cin, current->data.title);
            cout << "Enter new author: ";
            getline(cin, current->data.author);
            cout << "Enter new year: ";
            cin >> current->data.year;
            cin.ignore();
            return true;
        }
        current = current->next;
    }
    return false;
}

void displayLinkedList(Node *head)
{
    if (head == NULL)
    {
        cout << "Linked list is empty.\n";
        return;
    }
    cout << "\nBook List (Linked List):\n";
    cout << left << setw(5) << "No."
         << setw(25) << "Title"
         << setw(20) << "Author"
         << setw(8) << "Year"
         << setw(20) << "Insert Time" << endl;

    Node *current = head;
    int index = 1;
    while (current != NULL)
    {
        cout << left << setw(5) << index++
             << setw(25) << current->data.title
             << setw(20) << current->data.author
             << setw(8) << current->data.year
             << setw(20) << current->insertTime << endl;
        current = current->next;
    }
}

void cleanUp(Node *&head)
{
    delete[] bookArray;
    bookArray = NULL;
    bookCount = 0;

    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

Book inputBooksSingle()
{
    Book b;
    cout << "Enter book title: ";
    getline(cin, b.title);
    cout << "Enter author: ";
    getline(cin, b.author);
    cout << "Enter year: ";
    cin >> b.year;
    cin.ignore();
    return b;
}
int main()
{
    Node *bookListHead = NULL;

    inputBooks();
    displayBookArray();

    for (int i = 0; i < bookCount; ++i)
    {
        insertEnd(bookListHead, bookArray[i], false);
    }

    displayLinkedList(bookListHead);

    cout << "\nSorting books by title in array...\n";
    sortBooks();
    displayBookArray();

    string searchTitle;
    cout << "\nEnter book title to search (Linear Search): ";
    getline(cin, searchTitle);
    int index = linearSearch(searchTitle);
    if (index != -1)
        cout << "Found at position " << index + 1 << " in array.\n";
    else
        cout << "Book not found.\n";

    cout << "\nEnter book title to search (Binary Search): ";
    getline(cin, searchTitle);
    index = binarySearch(searchTitle);
    if (index != -1)
        cout << "Found at position " << index + 1 << " in sorted array.\n";
    else
        cout << "Book not found.\n";

    int choice;
    do
    {
        cout << "\n--- Linked List Operations Menu ---\n";
        cout << "1. Insert book at beginning\n";
        cout << "2. Insert book at end\n";
        cout << "3. Insert book in the middle (after a title)\n";
        cout << "4. Delete from beginning\n";
        cout << "5. Delete from end\n";
        cout << "6. Delete from middle (by position)\n";
        cout << "7. Update book info by title\n";
        cout << "8. Display linked list\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        Book b;
        string targetTitle;
        int pos;

        switch (choice)
        {
        case 1:
            cout << "Insert book at beginning:\n";
            b = inputBooksSingle();
            insertAtBeginning(bookListHead, b);
            break;
        case 2:
            cout << "Insert book at end:\n";
            b = inputBooksSingle();
            insertEnd(bookListHead, b);
            break;
        case 3:
            cout << "Insert book after a specific title:\n";
            cout << "Enter the title to insert after: ";
            getline(cin, targetTitle);
            b = inputBooksSingle();
            if (!insertAfterTitle(bookListHead, targetTitle, b))
                cout << "Title not found in list.\n";
            break;
        case 4:
            if (!deleteFromBeginning(bookListHead))
                cout << "List is empty. Cannot delete.\n";
            else
                cout << "Deleted from beginning.\n";
            break;
        case 5:
            if (!deleteFromEnd(bookListHead))
                cout << "List is empty. Cannot delete.\n";
            else
                cout << "Deleted from end.\n";
            break;
        case 6:
            cout << "Enter position to delete from (1-based): ";
            cin >> pos;
            cin.ignore();
            if (!deleteFromMiddle(bookListHead, pos))
                cout << "Invalid position.\n";
            else
                cout << "Deleted from position " << pos << ".\n";
            break;
        case 7:
            cout << "Enter title to update: ";
            getline(cin, targetTitle);
            if (!updateBookInfo(bookListHead, targetTitle))
                cout << "Title not found.\n";
            else
                cout << "Book info updated.\n";
            break;
        case 8:
            displayLinkedList(bookListHead);
            break;
        case 9:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    cleanUp(bookListHead);

    return 0;
}
