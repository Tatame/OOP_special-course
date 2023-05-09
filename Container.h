#include <iostream>

#ifndef LAB3_CONTAINER_H
#define LAB3_CONTAINER_H

template<class T>
class Container{

public:
    struct Node {
        T* value;
        Node *early;
        Node *next;

        explicit Node(T* val, Node* e = nullptr, Node* n = nullptr) {
            value = val;
            early = e;
            next = n;
        }
    };

    class iterator{
    public:
        iterator() : current{nullptr} {}

        T* operator*(){
            return current->value;
        }

        iterator& operator++(){
            current = current->next;
            return *this;
        }

        iterator& operator--(){
            current = current->early;
            return *this;
        }

        bool operator==(const iterator &other) const {
            return current == other.current;
        }

        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

    protected:
        Node* current;
        explicit iterator(Node *p) : current{p} {}
        friend class Container<T>;
    };

public:
    iterator begin() noexcept{
        return iterator(head);
    }

    iterator end() noexcept{
        return iterator(tail->next);
    }

public:
    Container(){
        create();
    }

    Container& operator=(const Container &other)  {
        Container copy = other;
        std::swap(*this, copy);
        return *this;
    }

    ~Container(){
        clear();
    }

public:
    uint32_t size(){
        return container_size;
    }

    bool is_empty(){
        return container_size == 0;
    }

    void push_front(T* val){
        if (is_empty()) create_first(val);
        else {
            Node* tmp = new Node(val);
            tmp->next = head;
            head->early = tmp;
            head = tmp;
            container_size += 1;
        }
    }

    void push_back(T* val){
        if (is_empty()) create_first(val);
        else {
            Node* tmp = new Node(val);
            tmp->early = tail;
            tail->next = tmp;
            tail = tmp;
            container_size += 1;
        }
    }

    void pop_front(){
        if (!is_empty()){
            Node* tmp = head;
            head = head->next;
            if (head) head->early = nullptr;
            delete tmp;
            container_size -= 1;
        }
        else throw std::out_of_range("Container is empty");
    }

    void pop_back(){
        if (!is_empty()){
            Node* tmp = tail;
            tail = tail->early;
            if (tail) tail->next = nullptr;
            delete tmp;
            container_size -= 1;
        }
        else throw std::out_of_range("Container is empty");
    }

    void clear(){
        while (!is_empty()){
            pop_front();
        }
    }

    T* get_first_element(){
        if (!is_empty()){
            return head->value;
        }
        else throw std::out_of_range("Container is empty");
    }

    T* get_last_element(){
        if (!is_empty()){
            return tail->value;
        }
        else throw std::out_of_range("Container is empty");
    }

    void swap(Container& other){
        Node* tmp;
        tmp = head;
        head = other.head;
        other.head = tmp;
        tmp = tail;
        tail = other.tail;
        other.tail = tmp;
        auto len = container_size;
        container_size = other.container_size;
        other.container_size = len;
    }

    void swap(iterator& it1, iterator& it2){
        std::iter_swap(it1, it2);
    }

    void reverse() noexcept {
        auto it1 = begin();
        auto it2 = iterator(tail);
        uint32_t count = container_size/2;
        while (count--) {
            swap(it1, it2);
            ++it1;
            --it2;
        }
    }

public:


private:
    void create() {
        container_size = 0;
        head = nullptr;
        tail = nullptr;
    }

    void create_first(T* val){
        head = new Node(val, nullptr, nullptr);
        tail = head;
        container_size = 1;
    }

private:
    Node* head;
    Node* tail;
    uint32_t container_size{};
};

#endif //LAB3_CONTAINER_H
