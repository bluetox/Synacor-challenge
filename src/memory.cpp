#include "memory.hpp"
#include "typesconsts.hpp"
#include <fstream>
#include <iostream>

Memory::Memory() {

  this->mem = new Address[MEM_SIZE]{};
  this->instruction_ptr = 0;

  std::ifstream rf(CHALLENGE_PATH, std::ios::binary);

  if (!rf)
    throw std::runtime_error("Impossible de trouver le fichier");
  

  Address value;
  int i = 0;
  while (i < MEM_SIZE &&
         rf.read(reinterpret_cast<char *>(&value), sizeof(value))) {
    this->mem[i++] = value;
  }
  this->context_size = i;
  rf.close();

  std::cout << "Memory initialized" << std::endl;
}

Address Memory::instr_ptr() {
  return this->instruction_ptr;
}

Address Memory::read_next() {
  if (this->instruction_ptr >= this->context_size)
    throw std::runtime_error("Instruction pointer out of bounds");
  return this->mem[this->instruction_ptr++];
}

Address Memory::read_address(Address addr) {
  if (addr >= MEM_SIZE) 
    throw std::runtime_error("Tried to read outside of memory");
  return this->mem[addr];
}

void Memory::write_address(Address addr, Address value) {
  if (addr >= MEM_SIZE)
    throw std::runtime_error("Tried to write outside of memory");
  this->mem[addr] = value;
}

void Memory::jump(Address addr) {
  if (addr < MEM_SIZE) 
    this->instruction_ptr = addr;
   else 
    throw std::runtime_error("Jumped to invalid memory location, exiting....");
}

Memory::~Memory() { delete[] mem; }
