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

    void delete_val(int value) { //Method that deletes a specific value
        if (!head) return; //Returns if the list is empty

        Node* temp = head; //Starts from the head using a temp pointer
        
        while (temp && temp->data != value) //If both temp exists and the value of temp isnt the value we want to delete, will keep going forward from the next pointer
            temp = temp->next;

        if (!temp) return;  //If there is null then it returns

        if (temp->prev) //Since we're deleting the value of temp, we want to connect the previous node's next to the node after temp
            temp->prev->next = temp->next;
        else //If there is nothing behind the value we want to delete, it means temp is the head. we just set the head to be the node after temp
            head = temp->next; 

        if (temp->next) //If temp has a next(makes sure we don't edit null things)
            temp->next->prev = temp->prev; //Sets the next node's prev pointer to point to the node before temp
        else //Sets it as the tail if it's the last node(ie temp->next points to nothing)
            tail = temp->prev; 

        delete temp; //Once the next and prev of the nodes next to temp is connected, deletes the temp node (the node with the value we want)
    }

    void delete_pos(int pos) { //Method that deletes the position we input
        if (!head) { //List is empty
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { //If the position is the head, we just call the other method that deletes the head
            pop_front();
            return;
        }
    
        Node* temp = head; //Temp ptr that starts from the head
    
        for (int i = 1; i < pos; i++){ //Goes through the entire list, until i is the position we're looking for
            if (!temp) { //If temp is null, aka doesn't exist
                cout << "Position doesn't exist." << endl;
                return;
            }
            else //Keeps going through the list
                temp = temp->next;
        }
        if (!temp) { //Doesn't exist
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { //If it's the last value, calls method that deletes tail
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev; //The node preceding the current position
        tempPrev->next = temp->next; //Previous node now points to node after current position
        temp->next->prev = tempPrev; //Node after current points to previous node, connecting the two together so we can delete temp
        delete temp; //Deletes temp node
    }

    void push_back(int v) { //Method that adds a value to the end of the list
        Node* newNode = new Node(v); //Initializes a new node with the value
        if (!tail) //If list is empty, the new node is set as the head and tail
            head = tail = newNode;
        else { //If list is not empty
            tail->next = newNode; //current tail points to the new node
            newNode->prev = tail; //New node points to current tail
            tail = newNode; //Tail now becomes new node
        }
    }
    
    void push_front(int v) { //Method that adds a value to the front of the code
        Node* newNode = new Node(v); //Initializes new node with value
        if (!head) //If list is empty, new node becomes head and tail
            head = tail = newNode;
        else { 
            newNode->next = head; //Node points to the current head 
            head->prev = newNode; //Head prev points to the new node
            head = newNode; //Head now becomes the new node
        }
    }
    
    void pop_front() { //Method that deletes the head value/or node in the front of the list

        if (!head) { //Empty
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; //Pointer starts from the head

        if (head->next) { //If more than 1 node exists
            head = head->next; //Head is now the node that comes after
            head->prev = nullptr; //Previous points to nothing since it's the first value
        }
        else //If only the head exists, both tail and head point to nothing
            head = tail = nullptr; 
        delete temp;
    }

    void pop_back() { //Method that deletes the tail/node that comes last
        if (!tail) { //Empty
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail; //Starts from tail

        if (tail->prev) { //If more than 1 node
            tail = tail->prev; //Tail is now the value that comes before
            tail->next = nullptr; //Next points to nothing since it's last value
        }
        else //If only node is tail, both head and tail point to nothing
            head = tail = nullptr;
        delete temp; 
    }

    ~DoublyLinkedList() { //Deconstructor, deletes all the list
        while (head) { //Makes sure head exists
            Node* temp = head; //Points to the node in the head currently
            head = head->next; //Makes the new head the node that comes after
            delete temp; //Deletes the current node
        }
    }
    void print() { //Method that prints the entire list
        Node* current = head; //Starts from head
        if (!current) { //Empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) { //For each node, will print the current value and then move on to the next, until empty
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() { //Method that prints the list beginning from the tail
        Node* current = tail; //Starts from tail
        if (!current) { //Empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) { //For each node, will print the current value and then move on to the previous one, until empty
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_element() { //Method that will print every other element, skipping even positions
        Node* current = head; //Starts from the head
        if (!current) { //Empty
            cout << "List is empty." << endl;
            return;
        }
        int count = 0; //Checker for whether we are on an odd position or even (Value starts from 0, so technically first position is the count 0, second position is count 1, etc.)
        while (current) {
            if (count % 2 == 0) { //If the position is odd
                cout << current->data << " "; //Prints
            }
            current = current->next; //Keeps going on to the next value
            count++; //Adds one to the count
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    DoublyLinkedList * DLL = new DoublyLinkedList; //New doubly linked list
    //Adding values
    DLL->push_back(6); 
    DLL->push_back(7);
    DLL->push_back(2);
    DLL->push_back(5);
    //Testing
    DLL->every_other_element();

    return 0;
}