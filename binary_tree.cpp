#include "binary_tree.h"
#include <iostream>
#include <stack>
#include "stdexcept"

using namespace std;

template <class T>
T BinaryTree<T>::find(int key) {
   Node* current = head;

    while (current!= nullptr){
        if (current->key == key)
            return current->value;

        if(key < current->key)
            current=current->left;
        else
            current=current->right;
    }
    //no such key found!
    throw logic_error("no such node found!");
}

/**
 * Same method as find given in header
 * @param key of the node
 * @param head of the binary tree
 * @return found node (if exists) or nullptr if not found
 */
template <class T>
class BinaryTree<T>::Node* findNode(int key, class BinaryTree<T>::Node* head) {
    class BinaryTree<T>::Node* current = head;

    while (current!= nullptr){
        if (current->key == key)
            return current;

        if(key < current->key)
            current=current->left;
        else
            current=current->right;
    }
    //no such key found!
    return nullptr;
}

template <class T>
void BinaryTree<T>::insert(int key, T value) {
    Node* n = findNode<T>(key,head);
    if (n != nullptr)
        throw logic_error("the given key already exists!");

    Node* node = new Node(key, value);//new node we want to insert
    Node* current = head;
    Node* temp = nullptr;

    //there was nothing in a tree
    if (current == nullptr){
        head = node;
        size = 1;
        return;
    }

    //choose the parent for a new node
    do{
        temp = current;
        if (node->key < current->key)
            current = current->left;
        else
            current = current->right;
    }while (current!= nullptr);

    //check for the node to be on the right or on the left
    if (node->key<temp->key)
        temp->left=node;
    else
        temp->right=node;

    size++;
}

/**
 * method to find a minimum key in a subtree
 * @param node a head of a substring
 * @return min node in a substring
 */
template <class T>
class BinaryTree<T>::Node* findMin(class BinaryTree<T>::Node* node){
    if (node == nullptr)
        throw logic_error("no node to look for!");

    while (node->left != nullptr)
        node = node->left;//min is always on the left

    return node;
}

/**
 * method to find node's parent if exist
 * @param node
 * @param head of the binary tree
 * @return node's parent
 */
template <class T>
class BinaryTree<T>::Node* parent(class BinaryTree<T>::Node* node, class BinaryTree<T>::Node* head){
    if (node== nullptr || head== nullptr)
        throw logic_error("Can't be null!");

    if (node == head)
        return nullptr;//no parent for head

    class BinaryTree<T>::Node* current = head;

    while (current!= nullptr && current->left!=node && current->right!=node){
        if (current->key > node->key)
            current = current->left;
        else
            current = current->right;
    }

    return current;
}

template <class T>
void BinaryTree<T>::remove(int key) {
    Node* node = findNode<T>(key,head);//so node to remove

    if (node == nullptr)
        throw logic_error("No such node found to remove!");
    if (head == nullptr)
        throw logic_error("Tree is empty!");

    Node* p = parent<T>(node,head);//parent for the node
    //node doesn't have any children
    if (node->left == nullptr && node->right == nullptr)
    {
        if (p == nullptr)//means node==head
        {
            head = nullptr;
            delete node;
            size=0;
            return;
        }
        //remove pointers
        if (p->left==node)
            p->left= nullptr;
        else
            p->right= nullptr;

        size--;
        delete node;
        return;
    }
    //node has both children
    if (node->left!= nullptr && node->right!= nullptr){
        Node* successor = findMin<T>(node->right);//to put instead removing
        Node* par = parent<T>(successor,head);//parent of the node

        if (par->key!=node->key)
            par->left=successor->right;
        else
            node->right= successor->right;

        node->key=successor->key;//settling the right pointers
        node->value=successor->value;

        successor = nullptr;
        delete successor;

        size--;

        return;
    }
    //case node has one child
    Node* ch;//get a child
    if (node->left == nullptr)
        ch=node->right;
    else
        ch=node->left;
    if (p == nullptr)//if no parent, then child is now the head
        head=ch;
    else if (p->left != nullptr && p->left==node)
        p->left=ch;
    else if (p->right != nullptr && p->right==node)
        p->right=ch;
    size--;
    delete node;
}

/**
 * method to delete a subtree
 * @param n head of a subtree
 */
template <class T>
void delN(class BinaryTree<T>::Node*n){
    if (n!= nullptr){
        delN<T>(n->right);
        delN<T>(n->left);
        delete n;
    }
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    delN<T>(head);
    head=nullptr;
    size=0;
}

template <class T>
void BinaryTree<T>::TraverseNode(Node *start, T (*func)(T)) {
    if (start== nullptr || func== nullptr)
        throw logic_error("Head or function can't be null!");
    stack<Node*> stack1;//arranging a stack of nodes
    Node* current = start;

    while (current!= nullptr || !stack1.empty()){
        if (current!= nullptr){
            stack1.push(current);
                current = current->left;//going to the left side
        } else{
            current = stack1.top();//getting the top of the stack (lowest left leaf)
            current->value = func(current->value);//using a function
            stack1.pop();//removing node from the stack
            current=current->right;//moving to the right side throw the root
        }
    }
}
