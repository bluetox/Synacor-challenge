#ifndef CONTEXT_H
#define CONTEXT_H

#include "typesconsts.hpp"

class Context {
  Address *mem;

public:
  int instr_ptr = 0;
  Context();
  ~Context();
  Address read_address(Address addr);
  void write_address(Address addr, Address value);

  Address read_next();
  void jump(Address addr);
};

#endif