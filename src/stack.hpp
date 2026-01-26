#ifndef STACK_H
#define STACK_H

#include "typesconsts.hpp"

class Stack {
    Address *stack;
    int stack_pointer = 0;
public:
    Stack();
    void push(Address v);
    Address pop();
    bool empty();
    ~Stack();
};
#endif