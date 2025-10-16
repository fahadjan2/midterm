// COMSC-210 | Midterm #1 | Fahad Fawad Ahmad 
// IDE used: Visual Studio
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; //Constant values, unchangable, usually used for things like size that you want to be constant throughout the code

class DoublyLinkedList { //creates a class, something with members and methods that you can reuse. Doubly linked lists make it easier to navigate between data connecting them like nodes
private: //Makes sure you can't access these members outside the class itself
    struct Node { //Creates a struct of Node, with members except without private/public. Node is a doubly linked list with a previous and a next pointer, pointing to another node 
        int data; //Integer
        Node* prev; //Previous pointer, points to a node behind
        Node* next; //Next pointer, points to the node linked after it
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //Constructor that initializes the three variables above
            data = val; //Sets the data integer with a value when called
            prev = p; //Nullptr for previous value
            next = n; //Nullptr for next
        }
    };

    Node* head; //Head pointer, holds the first value in the linked list
    Node* tail; //Tail pointer, holds the last value in the linked list, both make it easier to access the fronts and ends
    

public: //Public makes sure that it can be accessed even outside of the class, usually where methods are stored
    DoublyLinkedList() { head = nullptr; tail = nullptr; } //Constructor when doublylinkedlist is initialized, sets head and tail as nullptr, pointing to nothing

    void insert_after(int value, int position) { //Method that takes in two parameters, a value int and a position int, then inserts a new value after the position
        if (position < 0) { //If the position is less than 0, will return since negatives don't exist as a position
            cout << "Position must be >= 0." << endl; 
            return;
        }

        Node* newNode = new Node(value); //Initializes a new node, the prev and next pointer being null, while value being set as the data member
        if (!head) { //If there is no node that currently exists in the doublylinkedlist, will set both the tail and head as the new node, then returns since there is no need to add it anywhere
            head = tail = newNode;
            return;
        }

        Node* temp = head; //Stores a temporary variable of node, to start from the head
        for (int i = 0; i < position && temp; ++i) //For each position in the linked list that starts from 0, it will keep going through the next pointer until it meets the position it wants. Makes sure temp exists 
            temp = temp->next;

        if (!temp) { //If there is no temp, it returns and deletes the new node. Means that the position is more than the amount in the list
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        //Once successfully found position, will try to set the next and previous values in a way to connect the new node in between
        newNode->next = temp->next; //The new node's next pointer now points to what the current position points to
        newNode->prev = temp; //The new node's previous pointer just points to the current position, since we want to insert it after
        if (temp->next) //Sets the node that was originally after the current position's, to point backwards to the new node
            temp->next->prev = newNode;
        else //If a next doesnt exist, then the last value / tail just points to the new node
            tail = newNode;
        temp->next = newNode; //Changes the current position's next to the new node, successfully connecting them
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_element() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        int count = 0;
        while (current) {
            if (count % 2 == 0) {
                cout << current->data << " ";
            }
            current = current->next;
            count++;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    cout << "\ntest3" << endl;
    DoublyLinkedList * DLL = new DoublyLinkedList;
    DLL->push_back(6);
    DLL->push_back(7);
    DLL->push_back(2);
    DLL->push_back(5);
    DLL->every_other_element();

    return 0;
}