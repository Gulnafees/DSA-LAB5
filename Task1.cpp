#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Node structure for each browser tab
struct node {
    int id;
    string title;
    string link;
    node* next;
    node* prev;

    node(int i,string t,  string l)
        : id(i),title(t),link(l), next(nullptr), prev(nullptr) {}
};

// 1. Create a new tab in the circular doubly linked list
void newTab(node*& head, node*& current, int id, string title, string link) {
    node* newNode = new node(id, title, link);

    if (head == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        current = newNode;
    }
    else {
        newNode->next = current->next;
        newNode->prev = current;

        current->next->prev = newNode;
        current->next = newNode;
        current = newNode;
    }
}

// 2. Close the current tab and keep the list circular
void closeCurrentTab(node*& head, node*& current) {
    if (head == nullptr) {
        cout << "No tab is open" << endl;
        return;
    }

    if (current->next == current) {
        delete current;
        head = nullptr;
        current = nullptr;
        return;
    }

    node* prevTab = current->prev;
    node* nextTab = current->next;

    prevTab->next = nextTab;
    nextTab->prev = prevTab;

    if (current == head) {
        head = nextTab;
    }

    delete current;
    current = nextTab;
}

// 3.Move to the next tab
void moveNext(node*& current) {
    if (current == nullptr) {
        cout << "No tab is open" << endl;
    }
    else if (current->next == current) {
        cout << "Only one tab is open" << endl;
    }
    else {
        current = current->next;
    }
}

// 4.Move to the previous tab
void movePrev(node*& current) {
    if (current == nullptr) {
        cout << "No tab is open" << endl;
    }
    else if (current->prev == current) {
        cout << "Only one tab is open" << endl;
    }
    else {
        current = current->prev;
    }
}

// 5. Display current tab and show its details
void displyCT(node* current) {
    if (current == nullptr) {
        cout << "No tab is open to show" << endl;
    }
    else {
        cout << "Current Tab: " << current->id << endl;
        cout << current->title << " " << current->link << endl;
    }
}

// 6. Display all tabs in forward direction, it start from current tab
void displayATF(node* current) {
    if (current == nullptr) {
        cout << "No tab is open to show" << endl;
        return;
    }

    node* start = current;
    node* temp = current;

    do {
        cout << "Tab id: " << temp->id;
        cout << " | Title: " << temp->title;
        cout << " | Link: " << temp->link << endl;
        temp = temp->next;
    } while (temp != start);
}

// 7. Display all tabs in backward direction
void displayATB(node* current) {
    if (current == nullptr) {
        cout << "No tab is open to show" << endl;
        return;
    }

    node* start = current;
    node* temp = current;

    do {
        cout << "Tab id: " << temp->id;
        cout << " | Title: " << temp->title;
        cout << " | Link: " << temp->link << endl;
        temp = temp->prev;
    } while (temp != start);
}

// 8. Search tab by ID
int SID(node* current, int id) {
    if (current == nullptr) {
        cout << "No tab is open to search" << endl;
        return -1;
    }

    node* start = current;
    node* temp = current;

    do {
        if (temp->id == id) {
            cout << "Tab id: " << temp->id;
            cout << " | Title: " << temp->title;
            cout << " | Link: " << temp->link << endl;
            return 1;
        }
        temp = temp->next;
    } while (temp != start);

    cout << "Tab ID " << id << " not found." << endl;
    return 0;
}

int main() {
    node* head = nullptr;
    node* current = nullptr;
    int choice = 0;

    cout << "=== Browser Tab Manager ==" << endl;

    do {
        cout << "\n1. Open a new tab" << endl;
        cout << "2. Close current tab" << endl;
        cout << "3. Move to next tab" << endl;
        cout << "4. Move to previous tab" << endl;
        cout << "5. Display current tab" << endl;
        cout << "6. Display all tabs forward" << endl;
        cout << "7. Display all tabs backward" << endl;
        cout << "8. Search tab by ID" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                string title;
                string link;

                cout << "Enter tab ID: ";
                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid tab ID." << endl;
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter tab title: ";
                getline(cin, title);
                cout << "Enter tab link: ";
                getline(cin, link);

                newTab(head, current, id, title, link);
                cout << "Tab opened." << endl;
                break;
            }
            case 2:
                closeCurrentTab(head, current);
                break;
            case 3:
                moveNext(current);
                break;
            case 4:
                movePrev(current);
                break;
            case 5:
                displyCT(current);
                break;
            case 6:
                displayATF(current);
                break;
            case 7:
                displayATB(current);
                break;
            case 8: {
                int id;
                cout << "Enter tab ID to search: ";
                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid tab ID." << endl;
                    break;
                }
                SID(current, id);
                break;
            }
            case 9:
                cout << "Exiting browser tab manager." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter 1-9." << endl;
        }
    } while (choice != 9);

    while (head != nullptr) {
        closeCurrentTab(head, current);
    }

    return 0;
}
