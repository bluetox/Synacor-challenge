#ifndef TYPESCONSTS_H
#define TYPESCONSTS_H

#define REGISTER_BASE_START 32768
#define REGISTER_BASE_END 32775
#define MEM_SIZE 32768
#define CHALLENGE_PATH "./challenge.bin"

enum Instructions {
    HALT,
    SET,
    PUSH,
    POP,
    EQ,
    GT,
    JMP,
    JT,
    JF,
    ADD,
    MULT,
    MOD,
    AND,
    OR,
    NOT,
    RMEM,
    WMEM,
    CALL,
    RET,
    OUT,
    IN,
    NOOP
};


using Register = unsigned short int;
using Address = Register;

#endif