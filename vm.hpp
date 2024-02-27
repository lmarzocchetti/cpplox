//
// Created by Lorenzo Marzocchetti on 27/02/24.
//

#ifndef CPPLOX_VM_HPP
#define CPPLOX_VM_HPP

#include "chunk.hpp"
#include "debug.hpp"

enum InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

struct VM {
    Chunk* chunk_;
    uint8_t* ip;

    VM();

    InterpretResult interpret(Chunk* chunk);

    void freeVM();
private:
    InterpretResult run();

    constexpr uint8_t READ_BYTE();
    constexpr Value READ_CONSTANT();
    constexpr Value READ_CONSTANT_LONG();
};

#endif //CPPLOX_VM_HPP
