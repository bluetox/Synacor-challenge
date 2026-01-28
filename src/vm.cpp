#include "vm.hpp"
#include "memory.hpp"
#include "stack.hpp"
#include "typesconsts.hpp"
#include <iostream>

bool isRegister(Register r) {
  if (r > REGISTER_BASE_END || REGISTER_BASE_START > r) {
    return false;
  } else {
    return true;
  }
}

Register VirtualMachine::readToValue() {
  return toValue(this->memory.read_next());
}

Register VirtualMachine::toValue(Register r) {
  if (r >= REGISTER_BASE_START && r <= REGISTER_BASE_END)
    return this->reg[r - REGISTER_BASE_START];
  else if (r < REGISTER_BASE_START)
    return r;
  else
    throw std::runtime_error("Tried to read a value of 16 bits");
}

VirtualMachine::VirtualMachine() : memory{}, reg{}, stack{} {};

void VirtualMachine::start() {
  std::cout << "Starting execution" << std::endl << std::endl;
  while (true) {
    Address instr = this->memory.read_next();
    switch (instr) {
    case Instructions::HALT:
      std::cout << "Stopping, opcode 0" << std::endl;
      return;

    case Instructions::SET: {
      Address a = this->memory.read_next();
      if (!isRegister(a))
        throw std::runtime_error("Invalid register");

      this->reg[a - REGISTER_BASE_START] = readToValue();
      break;
    }
    case Instructions::PUSH:
      this->stack.push(readToValue());
      break;

    case Instructions::POP: {
      Address a = this->memory.read_next();
      if (!isRegister(a))
        throw std::runtime_error("Invalid register");

      this->reg[a - REGISTER_BASE_START] = this->stack.pop();
      break;
    }
    case Instructions::EQ: {
      Address a = this->memory.read_next();
      if (!isRegister(a))
        throw std::runtime_error("Invalid register");

      if (readToValue() == readToValue()) {
        this->reg[a - REGISTER_BASE_START] = 1;
      } else {
        this->reg[a - REGISTER_BASE_START] = 0;
      }
      break;
    }
    case Instructions::GT: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      if (readToValue() > readToValue()) {
        this->reg[a - REGISTER_BASE_START] = 1;
      } else {
        this->reg[a - REGISTER_BASE_START] = 0;
      }
      break;
    }
    case Instructions::JMP: {
      Address a = readToValue();
      this->memory.jump(a);
      break;
    }
    case Instructions::JT:
      instr = readToValue();
      if (instr != 0) {
        instr = readToValue();
        this->memory.jump(instr);
      } else {
        readToValue();
      }
      break;
    case Instructions::JF:
      instr = readToValue();
      if (instr == 0) {
        instr = readToValue();
        this->memory.jump(instr);
      } else {
        readToValue();
      }
      break;

    case Instructions::ADD: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      this->reg[a - REGISTER_BASE_START] =
          (readToValue() + readToValue()) % 32768;
      break;
    }
    case Instructions::MULT: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      this->reg[a - REGISTER_BASE_START] =
          (readToValue() * readToValue()) % 32768;
      break;
    }
    case Instructions::MOD: {
      Address a = this->memory.read_next();
      Address b = readToValue();
      Address c = readToValue();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      if (c == 0) {
        this->reg[a - REGISTER_BASE_START] = 0;
      } else {
        this->reg[a - REGISTER_BASE_START] = (b % c) % 32768;
      }
      break;
    }
    case Instructions::AND: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      this->reg[a - REGISTER_BASE_START] = readToValue() & readToValue();
      break;
    }
    case Instructions::OR: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      this->reg[a - REGISTER_BASE_START] = readToValue() | readToValue();
      break;
    }
    case Instructions::NOT: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      this->reg[a - REGISTER_BASE_START] = (~readToValue()) & 0x7FFF;
      break;
    }
    case Instructions::RMEM: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      Address b = readToValue();
      this->reg[a - REGISTER_BASE_START] = this->memory.read_address(b);
      break;
    }
    case Instructions::WMEM: {
      Address a = readToValue();
      Address b = readToValue();
      this->memory.write_address(a, b);
      break;
    }
    case Instructions::CALL: {
      Address target = readToValue();
      this->stack.push(this->memory.instr_ptr());
      this->memory.jump(target);
      break;
    }
    case Instructions::RET: {
      this->memory.jump(this->stack.pop());
      break;
    }
    case Instructions::OUT:
      instr = readToValue();
      std::cout << static_cast<char>(instr & 0xFF);
      break;
    case Instructions::IN: {
      Address a = this->memory.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      if (this->input_pos >= this->input_buffer.size()) {
        std::getline(std::cin, this->input_buffer);
        this->input_buffer += '\n';
        this->input_pos = 0;
      }
      this->reg[a - REGISTER_BASE_START] =
          this->input_buffer[this->input_pos++] & 0x7FFF;
      break;
    }

    case Instructions::NOOP:
      break;

    default:
      std::cout << "Unsupported operation: " << instr << std::endl;
      return;
    }
  }
  std::cout << "Program shutting down" << std::endl;
}

VirtualMachine::~VirtualMachine() {}