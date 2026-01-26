#ifndef CONTEXT_H
#define CONTEXT_H

#include "typesconsts.hpp"

class Context {
  Address *mem;
  int context_size;
  int instruction_ptr = 0;

public:
  Context();
  Register instr_ptr();
  Address read_address(Address addr);
  Address read_next();
  void write_address(Address addr, Address value);
  void jump(Address addr);
    ~Context();
};

#endif