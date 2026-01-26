#include "stack.hpp"
#include "typesconsts.hpp"
#include <stdexcept>

Stack::Stack() { stack = new Address[STACK_SIZE]; }

void Stack::push(Address v) {
  if (stack_pointer >= STACK_SIZE) {
    throw std::runtime_error("stack overflow");
  }

  stack[stack_pointer++] = v;
}

Address Stack::pop() {
  if (stack_pointer == 0) {
    throw std::runtime_error("stack underflow");
  }

  return stack[--stack_pointer];
}

bool Stack::empty() { return stack_pointer == 0; }

Stack::~Stack() { delete[] stack; }