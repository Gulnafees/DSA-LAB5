#include <iostream>
#include <string>

using namespace std;

// struct representing a coach in the circular train system
struct CoachNode {
    int coachNum;
    string coachType;
    int capacity;
    int currentPassengers;
    CoachNode* next;
    CoachNode* prev;

    // constructor
    CoachNode(int num,string type, int cap,  int pass)
        : coachNum(num), coachType(type), capacity(cap), currentPassengers(pass),
          next(nullptr), prev(nullptr) {}
};

// 1. Add Coach - Append at end of train (before head / tail position)
void addCoach(CoachNode*& head, CoachNode*& current, int num, string type, int cap, int pass) {
    CoachNode* newCoach = new CoachNode(num, type, cap, pass);

    // if train empty
    if (head == nullptr) {
        newCoach->next = newCoach;
        newCoach->prev = newCoach;
        head = newCoach;
        current = newCoach;
    }
    else {
        CoachNode* tail = head->prev;
        newCoach->next = head;
        newCoach->prev = tail;
        tail->next = newCoach;
        head->prev = newCoach;
    }
    cout << "Added coach " << num << " to train end." << endl;
}

// 2. Insert Coach - Insert after a specified coach number
void insertCoachAfter(CoachNode*& head, CoachNode*& current, int targetNum, int num, string type, int cap, int pass) {
    if (head == nullptr) {
        cout << "Train empty! Adding as first coach." << endl;
        addCoach(head, current, num, type, cap, pass);
        return;
    }

    CoachNode* temp = head;
    bool found = false;
    do {
        if (temp->coachNum == targetNum) {
            found = true;
            break;
        }
        temp = temp->next;
    } while (temp != head);

    if (!found) {
        cout << "Coach " << targetNum << " not found in train!" << endl;
        return;
    }

    CoachNode* newCoach = new CoachNode(num, type, cap, pass);
    CoachNode* nextCoach = temp->next;

    newCoach->next = nextCoach;
    newCoach->prev = temp;
    temp->next = newCoach;
    nextCoach->prev = newCoach;

    cout << "Inserted coach " << num << " after coach " << targetNum << endl;
}

// 3. Helper to remove a specific node safely without memory leak
void removeCoachNode(CoachNode*& head, CoachNode*& current, CoachNode* target) {
    if (target == nullptr) return;

    // incase single coach train
    if (target->next == target) {
        delete target;
        head = nullptr;
        current = nullptr;
    }
    // incase multiple coaches
    else {
        CoachNode* prevCoach = target->prev;
        CoachNode* nextCoach = target->next;

        prevCoach->next = nextCoach;
        nextCoach->prev = prevCoach;

        if (target == head) {
            head = nextCoach;
        }

        // if diliting active current coach, next valid coach becomes current
        if (target == current) {
            current = nextCoach;
        }

        delete target; // free dynamic allocation
    }
}

// 3. Remove Coach by coach number
void removeCoach(CoachNode*& head, CoachNode*& current, int num) {
    if (head == nullptr) {
        cout << "Train is empty! Cannot remove." << endl;
        return;
    }

    CoachNode* temp = head;
    do {
        if (temp->coachNum == num) {
            cout << "Removing coach " << num << endl;
            removeCoachNode(head, current, temp);
            return;
        }
        temp = temp->next;
    } while (temp != head);

    cout << "Coach " << num << " not found in train!" << endl;
}

// 4. Move Forward - Move current to current->next
void moveForward(CoachNode*& current) {
    if (current == nullptr) {
        cout << "Train is empty!" << endl;
        return;
    }
    current = current->next;
    cout << "Moved forward to Coach " << current->coachNum << " (" << current->coachType << ")" << endl;
}

// 5. Move Backward - Move current to current->prev
void moveBackward(CoachNode*& current) {
    if (current == nullptr) {
        cout << "Train is empty!" << endl;
        return;
    }
    current = current->prev;
    cout << "Moved backward to Coach " << current->coachNum << " (" << current->coachType << ")" << endl;
}

// 6. Display train clockwise starting from current coach, it go around back
void displayClockwise(CoachNode* current) {
    if (current == nullptr) {
        cout << "Train is empty!" << endl;
        return;
    }

    CoachNode* startNode = current;
    CoachNode* temp = current;

    cout << "\n--- Train Display (Clockwise) ---\n";
    do {
        cout << "Coach #" << temp->coachNum 
             << " | Type: " << temp->coachType 
             << " | Capacity: " << temp->capacity 
             << " | Passengers: " << temp->currentPassengers;

        if (temp == current) {
            cout << "  <-- Current Selected";
        }
        cout << endl;

        temp = temp->next; // forward traversal using next
    } while (temp != startNode); // stops when reaching start coach again
}

// 7. Display Train Anti-clockwise starting from current node
void displayAntiClockwise(CoachNode* current) {
    if (current == nullptr) {
        cout << "Train is empty!" << endl;
        return;
    }

    CoachNode* startNode = current;
    CoachNode* temp = current;

    cout << "\n--- Train Display (Anti-Clockwise) ---\n";
    do {
        cout << "Coach #" << temp->coachNum 
             << " | Type: " << temp->coachType 
             << " | Capacity: " << temp->capacity 
             << " | Passengers: " << temp->currentPassengers;

        if (temp == current) {
            cout << "  <-- Current Selected";
        }
        cout << endl;

        temp = temp->prev; // backward traversal using prev
    } while (temp != startNode);
}

// 8. Search Coach by coach number
void searchCoach(CoachNode* head, int num) {
    if (head == nullptr) {
        cout << "Train is empty!" << endl;
        return;
    }

    CoachNode* temp = head;
    do {
        if (temp->coachNum == num) {
            cout << "\n--- Coach Found Details ---\n";
            cout << "Coach Number : " << temp->coachNum << endl;
            cout << "Coach Type   : " << temp->coachType << endl;
            cout << "Capacity     : " << temp->capacity << endl;
            cout << "Passengers   : " << temp->currentPassengers << endl;
            cout << "Empty Seats  : " << (temp->capacity - temp->currentPassengers) << endl;
            return;
        }
        temp = temp->next;
    } while (temp != head);

    cout << "Coach number " << num << " not found!" << endl;
}

// 9. Find Maximum Available Capacity (Largest number of empty seats)
void findMaxCapacity(CoachNode* head) {
    if (head == nullptr) {
        cout << "Train is empty!" << endl;
        return;
    }

    CoachNode* maxCoach = head;
    int maxEmpty = head->capacity - head->currentPassengers;

    CoachNode* temp = head->next;
    while (temp != head) {
        int emptySeats = temp->capacity - temp->currentPassengers;
        if (emptySeats > maxEmpty) {
            maxEmpty = emptySeats;
            maxCoach = temp;
        }
        temp = temp->next;
    }

    cout << "\n--- Coach with Maximum Available Capacity ---\n";
    cout << "Coach #" << maxCoach->coachNum << " (" << maxCoach->coachType << ")" << endl;
    cout << "Max Empty Seats: " << maxEmpty << " (Capacity: " << maxCoach->capacity 
         << ", Passengers: " << maxCoach->currentPassengers << ")\n";
}

// 10. Display Current Coach
void displayCurrentCoach(CoachNode* current) {
    if (current == nullptr) {
        cout << "No coach currently selected (Train Empty)." << endl;
        return;
    }

    cout << "- Currently Selected Coach ---\n";
    cout << "Coach Number : " << current->coachNum << endl;
    cout << "Type         : " << current->coachType << endl;
    cout << "Capacity     : " << current->capacity << endl;
    cout << "Passengers   : " << current->currentPassengers << endl;
}

// 11. Reverse Train Direction in-place by swapping next & prev pointers
void reverseTrainDirection(CoachNode*& head, CoachNode*& current) {
    if (head == nullptr || head->next == head) {
        cout << "Train direction reversed (No pointer change needed for 0 or 1 coach)." << endl;
        return;
    }

    CoachNode* currNode = head;
    CoachNode* temp = nullptr;

    // Traverse CDLL and swap next and prev pointers for every node
    do {
        temp = currNode->next;
        currNode->next = currNode->prev;
        currNode->prev = temp;

        currNode = temp; // Move to next original node (which is now in temp)
    } while (currNode != head);

    // Old head's next points to old tail, update head to old tail
    head = head->next; 

    cout << "Train direction successfully reversed!" << endl;
}

// Memory cleanup at exit to prevent memory leaks
void freeTrainMemory(CoachNode*& head, CoachNode*& current) {
    if (head == nullptr) return;

    CoachNode* curr = head;
    do {
        CoachNode* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    } while (curr != head);

    head = nullptr;
    current = nullptr;
}

int main() {
    CoachNode* head = nullptr;
    CoachNode* current = nullptr;

    int totalCoaches;
    cout << "Enter initial number of coaches: ";
    cin >> totalCoaches;

    for (int i = 0; i < totalCoaches; i++) {
        int num, cap, pass;
        string type;
        cout << "\nEnter details for Coach " << (i + 1) << ":\n";
        cout << "Coach Number: ";
        cin >> num;
        cin.ignore();
        cout << "Coach Type (Economy/Business/Sleeper): ";
        getline(cin, type);
        cout << "Passenger Capacity: ";
        cin >> cap;
        cout << "Current Passengers: ";
        cin >> pass;

        addCoach(head, current, num, type, cap, pass);
    }

    int choice;
    do {
        cout << "\n=============TRAIN COACH NAVIGATION MENU =======\n";
        cout << "1.  Add Coach (At End)"<<endl;
        cout << "2.  Insert Coach After Specified Coach\n";
        cout << "3.  Remove Coach by Coach Number\n";
        cout << "4.  Move Forward\n";
        cout << "5.  Move Backward\n";
        cout << "6.  Display Train Clockwise"<<endl;
        cout << "7.  Display Train Anti-Clockwise\n";
        cout << "8.  Search Coach by Number\n";
        cout << "9.  Find Maximum Available Capacity\n";
        cout << "10. Display Current Selected Coach\n";
        cout << "11. Reverse Train Direction"<<endl;
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int num, targetNum,cap, pass;
        string type;

        switch (choice){
            case 1:
                cout << "Coach Number: "; cin >> num; cin.ignore();
                cout << "Coach Type: "; getline(cin, type);
                cout << "Capacity: "; cin >> cap;
                cout << "Current Passengers: "; cin >> pass;
                addCoach(head, current, num, type, cap, pass);
                break;
            case 2:
                cout <<"Enter Target Coach Number to insert after: "; cin >> targetNum;
                cout <<"New Coach Number: "; cin >> num; cin.ignore();
                cout <<"Coach Type: "; getline(cin, type);
                cout <<"Capacity: "; cin >> cap;
                cout << "Current Passengers: "; cin >> pass;
                insertCoachAfter(head, current, targetNum, num, type, cap, pass);
                break;
            case 3:
                cout <<"Enter Coach Number to remove: "; cin >> num;
                removeCoach(head, current, num);
                break;
            case 4:
                moveForward(current);
                break;
            case 5:
                moveBackward(current);
                break;
            case 6:
                displayClockwise(current);
                break;
            case 7:
                displayAntiClockwise(current);
                break;
            case 8:
                cout << "Enter Coach Number to search: "; cin >> num;
                searchCoach(head, num);
                break;
            case 9:
                findMaxCapacity(head);
                break;
            case 10:
                displayCurrentCoach(current);
                break;
            case 11:
                reverseTrainDirection(head, current);
                break;
            case 12:
                cout << "Exiting system & releasing memory..." << endl;
                freeTrainMemory(head, current);
                break;
            default:
                cout << "Invalid choice! Please enter 1-12." << endl;
        }
    } while (choice != 12);

    return 0;
}