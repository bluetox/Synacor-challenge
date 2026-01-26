#include "stack.hpp"
#include "typesconsts.hpp"
#include <stdexcept>

bool Stack::isempty() { return this->stack_pointer == 0; }

Stack::Stack() { this->stack = new Address[STACK_SIZE]; }

void Stack::push(Address v) {
  if (this->stack_pointer >= STACK_SIZE)
    throw std::runtime_error("stack overflow");

  this->stack[this->stack_pointer++] = v;
}

Address Stack::pop() {
  if (this->stack_pointer == 0)
    throw std::runtime_error("stack underflow");

  return this->stack[--this->stack_pointer];
}


Stack::~Stack() { delete[] this->stack; }