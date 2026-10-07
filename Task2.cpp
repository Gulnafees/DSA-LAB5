#include <iostream>
#include <string>

using namespace std;

// structure for photo node in circular doubly linked list
struct PhotoNode {
    int id;
    string name;
    string date;
    string location;
    PhotoNode* next;
    PhotoNode* prev;

    // constructor 
    PhotoNode(int i, string n, string d, string l)
        : id(i), name(n), date(d), location(l), next(nullptr), prev(nullptr) {}
};

// 1. Add photo at end of album
void addPhoto(PhotoNode*& head, PhotoNode*& current, int& totalPhotos, int id, string name, string date, string loc) {
    PhotoNode* newPhoto = new PhotoNode(id, name, date, loc);

    // if album empty
    if(head == nullptr) {
        newPhoto->next = newPhoto;
        newPhoto->prev = newPhoto;
        head = newPhoto;
        current = newPhoto;
    }
    // if non empty add before head (tail)
    else {
        PhotoNode* tail = head->prev;
        newPhoto->next = head;
        newPhoto->prev = tail;
        tail->next = newPhoto;
        head->prev = newPhoto;
    }

    totalPhotos++;
    cout << "Added photo to end: " << name << endl;
}

// 2. Insert photo after current selected photo
void insertAfterCurrent(PhotoNode*& head, PhotoNode*& current, int& totalPhotos, int id, string name, string date, string loc) {
    if (head == nullptr) {
        addPhoto(head, current, totalPhotos, id, name, date, loc);
        return;
    }

    PhotoNode* newPhoto = new PhotoNode(id, name, date, loc);
    PhotoNode* nextPhoto = current->next;

    newPhoto->next = nextPhoto;
    newPhoto->prev = current;
    current->next = newPhoto;
    nextPhoto->prev = newPhoto;

    // updated current pointer to new photo
    current = newPhoto;
    totalPhotos++;
    cout<<"Inserted photo after current: "<<name<<endl;
}

// helper function for removing photo safely without memory leak
void removeNode(PhotoNode*& head, PhotoNode*& current, int& totalPhotos, PhotoNode* targetNode) {
    if(targetNode == nullptr) return;

    // incase only 1 photo in list
    if (targetNode->next == targetNode) {
        delete targetNode;
        head = nullptr;
        current = nullptr;
    } 
    // incase multiple photos present
    else {
        PhotoNode* prevNode = targetNode->prev;
        PhotoNode* nextNode = targetNode->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        if (targetNode == head) {
            head = nextNode;
        }

        // if diliting active photo make next one active
        if (targetNode == current) {
            current = nextNode;
        }

        delete targetNode; // free dynamic allocation
    }

    totalPhotos--;
}

// 3. Remove Photo using Photo ID
void removePhotoById(PhotoNode*& head, PhotoNode*& current, int& totalPhotos, int id) {
    if (head == nullptr) {
        cout << "Album is empty!" << endl;
        return;
    }

    PhotoNode* temp = head;
    do {
        if(temp->id == id) {
            cout << "Removing photo ID: " << id << endl;
            removeNode(head, current, totalPhotos, temp);
            return;
        }
        temp = temp->next;
    }while(temp != head);

    cout << "Photo with ID " << id << " not found!" << endl;
}

// 4. Remove current photo
void removeCurrentPhoto(PhotoNode*& head, PhotoNode*& current, int& totalPhotos) {
    if(current == nullptr) {
        cout<<"No photo selected to remove."<<endl;
        return;
    }
    cout<<"Removing current photo: "<<current->name<<endl;
    removeNode(head, current, totalPhotos, current);
}

// 5. Move next photo
void moveNext(PhotoNode*& current) {
    if(current == nullptr) {
        cout << "no photo to show" << endl;
        return;
    }
    current = current->next;
    cout << "Moved to next: " << current->name << endl;
}

// 6. Move prev photo
void movePrev(PhotoNode*& current) {
    if(current == nullptr) {
        cout << "no photo to show" << endl;
        return;
    }
    current = current->prev;
    cout << "Moved to previous: " << current->name << endl;
}

// 7. Display album forward starting from current photo
void displayAlbumForward(PhotoNode* current) {
    if (current == nullptr) {
        cout<<"Album is empty!"<<endl;
        return;
    }

    PhotoNode* startNode = current;
    PhotoNode* temp = current;

    cout << "\n--- Display Album Forward ---\n";
    do{
        cout << "ID: " << temp->id 
             << " | Name: " << temp->name 
             << " | Date: " << temp->date 
             << " | Loc: " << temp->location;

        if (temp == current) {
            cout << "  <-- Current";
        }
        cout << endl;

        temp = temp->next; // forward using next
    } while(temp != startNode); // stops when reaching start node again
}

// 8. Display album backward starting from current photo
void displayAlbumBackward(PhotoNode* current) {
    if (current == nullptr) {
        cout << "Album is empty!" << endl;
        return;
    }

    PhotoNode* startNode = current;
    PhotoNode* temp = current;

    cout << "\n--- Display Album Backward ---\n";
    do {
        cout << "ID: " << temp->id 
             << " | Name: " << temp->name 
             << " | Date: " << temp->date 
             << " | Loc: " << temp->location;

        if (temp == current) {
            cout << "  <-- Current";
        }
        cout << endl;

        temp = temp->prev; // backward using prev
    } while (temp != startNode);
}

// 9. Search photo by ID
void searchPhoto(PhotoNode* head, int id) {
    if(head == nullptr) {
        cout << "Album empty!" << endl;
        return;
    }

    PhotoNode* temp = head;
    do {
        if(temp->id == id) {
            cout << "\n--- Photo Details Found ---\n";
            cout << "ID: " << temp->id << "\nName: " << temp->name 
                 << "\nDate: " << temp->date << "\nLocation: " << temp->location << endl;
            return;
        }
        temp = temp->next;
    }while(temp != head);

    cout<<"Photo ID "<<id<<" not found in album."<<endl;
}

// 10. Count photos in album
void countPhotos(int totalPhotos) {
    cout << "Total photos count in album: " << totalPhotos << endl;
}

// cleanup function to prevent memory leaks on exit
void freeAlbumMemory(PhotoNode*& head, PhotoNode*& current, int& totalPhotos) {
    if(head == nullptr) return;

    PhotoNode* curr = head;
    do {
        PhotoNode* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    } while(curr != head);

    head = nullptr;
    current = nullptr;
    totalPhotos = 0;
}

int main() {
    PhotoNode* head = nullptr;
    PhotoNode* current = nullptr;
    int totalPhotos = 0;

    int n;
    cout << "Enter number of initial photos: ";
    cin >> n;

    for(int i = 0; i<n; i++) {
        int id;
        string name, date, loc;
        cout << "\nEnter photo " << (i+1) << " details:\n";
        cout << "ID: ";
        cin >> id;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Date: ";
        getline(cin, date);
        cout << "Location: ";
        getline(cin, loc);

        addPhoto(head, current, totalPhotos, id, name, date, loc);
    }

    int choice;
    do {
        cout << "\n================ PHOTO ALBUM MENU ================\n";
        cout << "1. Add Photo (End)\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo by ID\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next\n";
        cout << "6. Move Previous\n";
        cout << "7. Display Album Forward\n";
        cout << "8. Display Album Backward\n";
        cout << "9. Search Photo\n";
        cout << "10. Count Photos\n";
        cout << "11. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int id;
        string name, date, loc;

        switch(choice) {
            case 1:
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Name: "; getline(cin, name);
                cout << "Date: "; getline(cin, date);
                cout << "Location: "; getline(cin, loc);
                addPhoto(head, current, totalPhotos, id, name, date, loc);
                break;
            case 2:
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Name: "; getline(cin, name);
                cout << "Date: "; getline(cin, date);
                cout << "Location: "; getline(cin, loc);
                insertAfterCurrent(head, current, totalPhotos, id, name, date, loc);
                break;
            case 3:
                cout << "Enter ID to remove: "; cin >> id;
                removePhotoById(head, current, totalPhotos, id);
                break;
            case 4:
                removeCurrentPhoto(head, current, totalPhotos);
                break;
            case 5:
                moveNext(current);
                break;
            case 6:
                movePrev(current);
                break;
            case 7:
                displayAlbumForward(current);
                break;
            case 8:
                displayAlbumBackward(current);
                break;
            case 9:
                cout << "Enter ID to search: "; cin >> id;
                searchPhoto(head, id);
                break;
            case 10:
                countPhotos(totalPhotos);
                break;
            case 11:
                cout << "Exiting program & clearing memory..." << endl;
                freeAlbumMemory(head, current, totalPhotos);
                break;
            default:
                cout << "Invalid choice selected!" << endl;
        }
    } while(choice != 11);

    return 0;
}