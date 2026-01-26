#include "context.hpp"
#include "typesconsts.hpp"
#include <fstream>
#include <iostream>

Context::Context() {

  this->mem = new Address[MEM_SIZE]{};
  this->instr_ptr = 0;
  std::ifstream rf("./vm_challenge/challenge.bin", std::ios::binary);

  if (!rf) {
    throw std::runtime_error("Impossible de trouver le fichier");
  }
  Address value;
  int i = 0;
  while (i < MEM_SIZE &&
         rf.read(reinterpret_cast<char *>(&value), sizeof(value))) {
    mem[i++] = value;
  }
  rf.close();
  std::cout << "Memory initialized" << std::endl;
}

Address Context::read_next() {
  if (instr_ptr >= MEM_SIZE)
    throw std::runtime_error("Instruction pointer out of bounds");
  return mem[instr_ptr++];
}
Address Context::read_address(Address addr) {
  if (addr >= MEM_SIZE) {
    throw std::runtime_error("Outside of memory");
  }
  return mem[addr];
}

void Context::write_address(Address addr, Address value) {
  if (addr >= MEM_SIZE) {
    throw std::runtime_error("Outside of memory");
  }
  mem[addr] = value;
}

void Context::jump(Address addr) {
  if (addr < MEM_SIZE) {
    instr_ptr = addr;
  } else {
    throw std::runtime_error("Jumped to invalid memory location, exiting....");
  }
}

Context::~Context() { delete[] mem; }
