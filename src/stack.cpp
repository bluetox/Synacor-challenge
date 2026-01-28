#include "stack.hpp"
#include <stdexcept>

Stack::Stack() {
    this->capacity = 256;
    this->stack_pointer = 0;
    this->stack = new Address[this->capacity];
}

void Stack::grow() {
    int new_capacity = this->capacity * 2;
    Address *new_stack = new Address[new_capacity];

    for (int i = 0; i < this->stack_pointer; ++i) {
        new_stack[i] = this->stack[i];
    }

    delete[] this->stack;
    this->stack = new_stack;
    this->capacity = new_capacity;
}

void Stack::push(Address v) {
    if (this->stack_pointer == this->capacity) {
        grow();
    }
    this->stack[this->stack_pointer++] = v;
}

Address Stack::pop() {
    if (isempty()) {
        throw std::runtime_error("stack underflow");
    }
    return this->stack[--this->stack_pointer];
}

bool Stack::isempty() const { 
    return this->stack_pointer == 0; 
}

Stack::~Stack() { 
    delete[] this->stack; 
}