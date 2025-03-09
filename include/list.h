//
// Created by Софья Фролова  on 21.10.2024.
//

#ifndef MATRIX_LIST_H
#define MATRIX_LIST_H

#endif //MATRIX_LIST_H
#include <iostream>

template <class T>
class List {

public:
    struct Node{
        T data;
        Node * next;
        Node(){
            data = 0;
            next = nullptr;
        }
        Node(T d, Node* n){
            data = d;
            next = n;
        }
    };
private:
    Node * first;
public:

    List(): first(nullptr) {};
 //
    List (const List& other){
        //std::cout<<3;
        if (!other.first){
            first = nullptr;
        }
        //std::cout<<2;
        this->first = new Node (other.first->data, nullptr);
        Node * current = first, * ocurrent = other.first;

       while (ocurrent->next) {
            current->next = new Node(ocurrent->next->data, nullptr);
            current = current->next;
            ocurrent = ocurrent->next;
        }
    }

    explicit List(int n, T deflt = T()) {
        if (n==0 or n < 0) {
            throw "List doesn't exict";
        }
       // std::cout<<2;
        first = new Node (deflt, nullptr);
        //Node * tmp = new Node (T(), nullptr);
        Node* current = first;

        for (int i = 0; i < n - 1; i++){
            Node* tmp = new Node (deflt, nullptr);
            current->next = tmp;
            current = current->next;
        }

    }
    ~List() {
        while (first) {
            Node * second = first->next;
            delete first;
            first = second;
        }
    }

    void Clear() {
        Node* current = first;
        Node* tmp = nullptr;
        while (current) {
            tmp = current->next;
            delete current;
            current = tmp;
        }
        first = nullptr;
    }

    List& operator=(const List& other) {
        if (!other.first) {
            first = nullptr;
            return *this;
        }

        this->Clear();

        first = new Node(other.first->data, nullptr);
        Node* current = first;
        Node* ocurrent = other.first;

        while (ocurrent->next) {
            current->next = new Node(ocurrent -> next -> data, nullptr);
            current = current -> next;
            ocurrent = ocurrent -> next;
        }

        return *this;
    }

    bool operator==(const List& l) const
    {
        Node* current = this->first;
        Node* ocurrent = l.first;

        while (current) {
            if (ocurrent == nullptr) return 0;

            if (current->data != ocurrent->data) return 0;

            current = current->next;
            ocurrent = ocurrent->next;
        }

        if (ocurrent != nullptr)
            return 0;
        else
            return 1;

    }


    T& operator[] (int index){

        if((index>=this->size()) || (index<0)){
            throw "Wrong index";
        }
        Node* current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    inline List<T>::Node* insert(T value, Node* prev) {
        Node* tmp = new Node;
        if (prev->next) {
            tmp->next = prev->next;
        }
        tmp->data = value;
        prev->next = tmp;
        return tmp;
    }

    inline List<T>::Node* insert_front(T value) {
        Node* first_first = new Node;
        first_first->next = first;
        first_first->data = value;
        first = first_first;
        return first;
    }

    inline List<T>::Node* insert_end(T value) {
        Node* current = first;


        while (current->next) {
            current = current -> next;
        }

        insert(value, current);
        return current->next;
    }

    inline List<T>::Node* erase(Node* prev){
       if (!prev) {
           throw "Prev nullptr";
       }
        Node* tmp = prev->next;
       if (!(prev->next)) {throw 1;}
       prev->next = tmp->next;
       delete tmp;

    }

    inline List<T>::Node* erase_front() {
        if(!first) {
            throw "Empty List";
        }
        Node* tmp = first;
        first = tmp-> next;
        delete tmp;
        return first;
    }

    inline List<T>::Node* erase_end() {
        if(!first) {
            throw "Empty List";
        }
        Node* current = first;


        while ((current->next)->next) {
            current = current -> next;
        }

        delete current->next;
        current ->next = nullptr;
        return first;
    }

    inline List<T>::Node* find(T value) {
        Node* current = first;
        while(current){
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    size_t size() {
        int size = 0;
        Node* current = first;
        while(current) {
            size++;
            current = current->next;
        }
        return size;
    }

    inline List<T>::Node* get_first(){
        return first;
    }

    friend std:: istream& operator>>(std::istream& istr, List& l)
    {
        Node* current = l.first;
        while (current) {
            istr>> current->data;
            current = current->next;
        }
        return istr;
    }

    friend std:: ostream& operator<<(std::ostream& ostr, List& l)
    {
        Node* current = l.first;
        while (current) {
            ostr << current->data;
            current = current->next;
        }
        return ostr;
    }






    //Задача из предложенного списка 2
    inline List<T>::Node* erase_last_selected(T value) {
        if (!first) {
            throw "Can't delete element in empty list";
        }

        if (!first->next) {
            if (first->data == value) {
                delete first;
                first = nullptr;
                return first;
            } else {
                return first;
            }
        }
        Node* current = first;

        Node* tmp = nullptr;
        Node* prev = nullptr;

        while (current->next->next) {
            if (value == current->next->data) {
                tmp = current->next;
                prev = current;
            }
            current = current -> next;
        }
        //std::cout << first << std::endl;
        //std::cout << tmp << std::endl;
        if (!tmp) {
            return first;
        }
        if (tmp == first) {
            first= first->next;
            delete tmp;
            return first;
        }
        prev->next = tmp->next;
        delete tmp;
        return first;
    }



    //class iterator
    class Iterator {
        Node *curr;

    public:

        Iterator(Node *node) {
            curr = node;
        }

        Iterator& operator++() {
            if (!curr->next) {
                throw "Out of range";
            }
            curr = curr->next;
            return *this;
        }

        //int* p = &y;

        Iterator operator++(int) {
            if (!curr->next) {
                throw "Out of range";
            }
            Iterator copy = *this;
            curr = curr->next;
            return copy;
        }

        T& operator*() {
            return curr->data;
        }

        T* operator->() {
            return &(curr->data);
        }

        friend bool operator!=(const Iterator& it1, const Iterator& it2) {
            return (it1.curr != it2.curr);
        }

        friend bool operator==(const Iterator& it1, const Iterator& it2) {
            return (it1.curr == it2.curr);
        }

    };

    Iterator begin() {
        return Iterator(first);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};