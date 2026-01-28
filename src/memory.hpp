#ifndef MEMORY_H
#define MEMORY_H

#include "typesconsts.hpp"

class Memory {
  Address *mem;
  int context_size;
  int instruction_ptr = 0;

public:
  Memory();
  Register get_context_size();
  Address* get_mem_ptr();
  Register instr_ptr();
  Address read_address(Address addr);
  Address read_next();
  void write_address(Address addr, Address value);
  void jump(Address addr);
    ~Memory();
};

#endif