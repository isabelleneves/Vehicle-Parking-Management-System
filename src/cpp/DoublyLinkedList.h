#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <string>

class DoublyLinkedList {

private:
    struct Node {
        std::string registrationNumber;
        Node* previous;
        Node* next;

        Node(std::string registration) {
            registrationNumber = registration;
            previous = nullptr;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void addVehicle(std::string registration) {

        Node* newNode = new Node(registration);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }

        std::cout << "Vehicle added to linked list: "
                  << registration << std::endl;
    }

    void displayForward() {

        Node* current = head;

        std::cout << "Vehicles (forward): ";

        while (current != nullptr) {
            std::cout << current->registrationNumber << " ";
            current = current->next;
        }

        std::cout << std::endl;
    }

    void displayBackward() {

        Node* current = tail;

        std::cout << "Vehicles (backward): ";

        while (current != nullptr) {
            std::cout << current->registrationNumber << " ";
            current = current->previous;
        }

        std::cout << std::endl;
    }

    ~DoublyLinkedList() {

        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

#endif
