#ifndef TYPESCONSTS_H
#define TYPESCONSTS_H

#define REGISTER_BASE_START 32768
#define REGISTER_BASE_END 32775
#define STACK_SIZE 10000
#define MEM_SIZE 32768
#define CHALLENGE_PATH "./challenge.bin"

using Register = unsigned short int;
using Address = Register;

#endif