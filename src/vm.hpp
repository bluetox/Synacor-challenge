#ifndef VM_H
#define VM_H

#include "memory.hpp"
#include "stack.hpp"
#include "typesconsts.hpp"
#include <string>

class VirtualMachine {
private:
  Memory memory;
  Register reg[8];
  std::string input_buffer;
  Register input_pos = 0;
  Stack stack;

private:
  Register toValue(Register r);
  Register readToValue();

public:
  VirtualMachine();
  void start();
  ~VirtualMachine();
};

#endif