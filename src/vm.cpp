#include "vm.hpp"
#include "context.hpp"
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

Register VirtualMachine::readToValue() { return toValue(this->context.read_next()); }

Register VirtualMachine::toValue(Register r) {
  if (r >= REGISTER_BASE_START && r <= REGISTER_BASE_END)
    return this->reg[r - REGISTER_BASE_START];
  else if (r < REGISTER_BASE_START)
    return r;
  else 
    throw std::runtime_error("Tried to read a value of 16 bits");
}

VirtualMachine::VirtualMachine() : context{}, reg{}, stack{} {};

void VirtualMachine::start() {
  std::cout << "Starting execution" << std::endl << std::endl;
  while (true) {
    Address instr = this->context.read_next();
    switch (instr) {
    case 0:
      std::cout << "Stopping, opcode 0" << std::endl;
      return;

    case 1: {
      Address a = this->context.read_next();
      if (!isRegister(a)) 
        throw std::runtime_error("Invalid register");
      
      reg[a - REGISTER_BASE_START] = readToValue();
      break;
    }
    case 2:
      stack.push(readToValue());
      break;

    case 3: {
      Address a = this->context.read_next();
      if (!isRegister(a))
        throw std::runtime_error("Invalid register");
      
      reg[a - REGISTER_BASE_START] = stack.pop();
      break;
    }
    case 4: {
      Address a = this->context.read_next();
      if (!isRegister(a))
        throw std::runtime_error("Invalid register");
  
      if (readToValue() == readToValue()) {
        reg[a - REGISTER_BASE_START] = 1;
      } else {
        reg[a - REGISTER_BASE_START] = 0;
      }
      break;
    }
    case 5: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      if (readToValue() > readToValue()) {
        reg[a - REGISTER_BASE_START] = 1;
      } else {
        reg[a - REGISTER_BASE_START] = 0;
      }
      break;
    }
    case 6: {
      Address a = readToValue();
      this->context.jump(a);
      break;
    }
    case 7:
      instr = readToValue();
      if (instr != 0) {
        instr = readToValue();
        this->context.jump(instr);
      } else {
        readToValue();
      }
      break;
    case 8:
      instr = readToValue();
      if (instr == 0) {
        instr = readToValue();
        this->context.jump(instr);
      } else {
        readToValue();
      }
      break;

    case 9: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      reg[a - REGISTER_BASE_START] = (readToValue() + readToValue()) % 32768;
      break;
    }
    case 10: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      reg[a - REGISTER_BASE_START] = (readToValue() * readToValue()) % 32768;
      break;
    }
    case 11: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      reg[a - REGISTER_BASE_START] = (readToValue() % readToValue()) % 32768;
      break;
    }
    case 12: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      reg[a - REGISTER_BASE_START] = readToValue() & readToValue();
      break;
    }
    case 13: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      reg[a - REGISTER_BASE_START] = readToValue() | readToValue();
      break;
    }
    case 14: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      reg[a - REGISTER_BASE_START] = (~readToValue()) & 0x7FFF;
      break;
    }
    case 15: {
      Address a = this->context.read_next();
      if (!isRegister(a)) {
        throw std::runtime_error("Invalid register");
      }
      Address b = readToValue();
      reg[a - REGISTER_BASE_START] = this->context.read_address(b);
      break;
    }
    case 16: {
      Address a = readToValue();
      Address b = readToValue();
      this->context.write_address(a, b);
      break;
    }
    case 17: {
      Address target = readToValue();
      stack.push(this->context.instr_ptr());
      this->context.jump(target);
      break;
    }
    case 18: {
      this->context.jump(stack.pop());
      break;
    }
    case 19:
      instr = readToValue();
      std::cout << static_cast<char>(instr & 0xFF);
      break;
    case 20: {
      Address a = this->context.read_next();
      if (input_pos >= input_buffer.size()) {
        std::getline(std::cin, input_buffer);
        input_buffer += '\n';
        input_pos = 0;
      }
      reg[a - REGISTER_BASE_START] = input_buffer[input_pos++] & 0x7FFF;
      break;
    }

    case 21:
      break;

    default:
      std::cout << "Unsupported operation: " << instr << std::endl;
      return;
    }
  }
  std::cout << "Program shutting down" << std::endl;
}

VirtualMachine::~VirtualMachine() {}