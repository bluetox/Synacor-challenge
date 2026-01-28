#ifndef STACK_H
#define STACK_H

#include "typesconsts.hpp"

class Stack {
private:
    Address *stack;
    int stack_pointer = 0;
    int capacity;
    void grow();
    

public:
    Stack();
    void push(Address v);
    Address pop();
    bool isempty() const;
    ~Stack();
};
#endif