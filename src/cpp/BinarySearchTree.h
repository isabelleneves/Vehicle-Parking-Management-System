#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <string>

class BinarySearchTree {

private:
    struct Node {
        std::string registrationNumber;
        Node* left;
        Node* right;

        Node(std::string registration) {
            registrationNumber = registration;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = nullptr;

    Node* insertNode(Node* node, std::string registration) {

        if (node == nullptr) {
            return new Node(registration);
        }

        if (registration < node->registrationNumber) {
            node->left = insertNode(node->left, registration);
        } else if (registration > node->registrationNumber) {
            node->right = insertNode(node->right, registration);
        }

        return node;
    }

    bool searchNode(Node* node, std::string registration) {

        if (node == nullptr) {
            return false;
        }

        if (registration == node->registrationNumber) {
            return true;
        }

        if (registration < node->registrationNumber) {
            return searchNode(node->left, registration);
        }

        return searchNode(node->right, registration);
    }

public:
    void insert(std::string registration) {

    if (search(registration)) {
        std::cout << "Vehicle already exists in search tree: "
                  << registration << std::endl;
        return;
    }

    root = insertNode(root, registration);

    std::cout << "Vehicle added to search tree: "
              << registration << std::endl;
}

    bool search(std::string registration) {
        return searchNode(root, registration);
    }

    void displayInOrder(Node* node) {

        if (node != nullptr) {
            displayInOrder(node->left);
            std::cout << node->registrationNumber << " ";
            displayInOrder(node->right);
        }
    }

    void display() {
        std::cout << "Vehicles in alphabetical order: ";
        displayInOrder(root);
        std::cout << std::endl;
    }
};

#endif
