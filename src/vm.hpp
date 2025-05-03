#pragma once

#include <stack>
#include <functional>

#include "chunk.hpp"
#include "debug.hpp"
#include "compiler.hpp"

enum class InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

struct VM {
    Chunk* chunk_;
    uint8_t* ip;
    std::stack<Value> stack;

    VM();
    ~VM();

    InterpretResult interpret(Chunk* chunk);
    InterpretResult interpret(const std::string& source);
private:
    void freeVM();
    InterpretResult run();

    void resetStack();
    void printStack() const;

    constexpr uint8_t READ_BYTE();
    constexpr Value READ_CONSTANT();
    constexpr Value READ_CONSTANT_LONG();
};