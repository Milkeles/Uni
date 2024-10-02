#ifndef STACK_H
#define STACK_H

template <class T>
struct node {
    T inf;
    node<T> * link;
};

template <class T>
class stack {
private:
    node<T>* top; 
public:
    stack() : top(nullptr) {}
    ~stack();
    void push(T const &);
    T pop();
    T peek();
    bool isEmpty() { return top == nullptr; }
    void printStack();
};

template <class T>
stack<T>::~stack() {
    while (top) {
        node<T> * temp = top;
        top = top->link;
        delete temp;
    }
}

template <class T>
void stack<T>::push(T const &data) {
    node<T> *newNode = new node<T>();
    newNode->inf = data;
    newNode->link = top;
    top = newNode;
}

template <class T>
T stack<T>::pop() {
    if(top) {
        node<T> * temp = top;
        T data = top->inf;
        top = top->link;
        delete temp;
        return data;
    } else {
        return NULL;
    }
}

template <class T>
T stack<T>::peek() {
    if (top) {
        return top->inf;
    } else {
        return NULL;
    }
}


template <class T>
void stack<T>::printStack() {
    node<T> * current = top;
    while(current) {
        std::cout << current->inf << ' ';
        current = current->link;
    }
    std::cout << std::endl;
}

#endif
