#ifndef STACK_H
#define STACK_H

#include "typesconsts.hpp"

class Stack {
private:
    Address *stack;
    int stack_pointer = 0;

private:
    bool isempty();

public:
    Stack();
    void push(Address v);
    Address pop();
    ~Stack();
};
#endif