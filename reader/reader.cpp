#include "../src/memory.hpp"
#include <cstdint>
#include <iostream>

void disassemble(Address *mem, Register size) {
  for (size_t i = 0; i < size;) {
    uint16_t opcode = mem[i];
    uint16_t addr = i;
    i++;

    switch (opcode) {
    case 0:
      std::cout << "HALT";
      break;
    case 1:
      std::cout << "SET  " << mem[i++] << " " << mem[i++];
      break;
    case 2:
      std::cout << "PUSH " << mem[i++];
      break;
    case 3:
      std::cout << "POP  " << mem[i++];
      break;
    case 4:
      std::cout << "EQ   " << mem[i++] << " " << mem[i++] << " " << mem[i++];
      break;
    case 5:
      std::cout << "GT   " << mem[i++] << " " << mem[i++] << " " << mem[i++];
      break;
    case 6:
      std::cout << "JMP  " << mem[i++];
      break;
    case 7:
      std::cout << "JT   " << mem[i++] << " " << mem[i++];
      break;
    case 8:
      std::cout << "JF   " << mem[i++] << " " << mem[i++];
      break;
    case 9:
      std::cout << "ADD  " << mem[i++] << " " << mem[i++] << " " << mem[i++];
      break;
    case 19: {
      uint16_t c = mem[i++];
      std::cout << "OUT  ";
      if (c == '\n')
        std::cout << "'\\n'";
      else
        std::cout << "'" << (char)c << "'";
      break;
    }
    default:
      std::cout << "DATA " << opcode;
      break;
    }
    std::cout << "\n";
  }
}

int main() {
  Memory mem{};
  disassemble(mem.get_mem_ptr(), mem.get_context_size());
  return 0;
}