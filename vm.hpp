//
// Created by Lorenzo Marzocchetti on 27/02/24.
//

#ifndef CPPLOX_VM_HPP
#define CPPLOX_VM_HPP

#include <stack>
#include <functional>

#include "chunk.hpp"
#include "debug.hpp"
#include "compiler.hpp"

enum InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

struct VM {
    Chunk* chunk_;
    uint8_t* ip;
    std::stack<Value> stack;

    VM();

    InterpretResult interpret(Chunk* chunk);
    InterpretResult interpret(const std::string& source);

    void freeVM();
private:
    InterpretResult run();

    void resetStack();
    void printStack() const;

    constexpr uint8_t READ_BYTE();
    constexpr Value READ_CONSTANT();
    constexpr Value READ_CONSTANT_LONG();
};

#endif //CPPLOX_VM_HPP
