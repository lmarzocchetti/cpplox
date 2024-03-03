//
// Created by Lorenzo Marzocchetti on 27/02/24.
//

#include "vm.hpp"

VM::VM() {
    resetStack();
}

InterpretResult VM::run() {
#define BINARY_OP(op)                 \
    do {                              \
        double b = this->stack.top(); \
        this->stack.pop();            \
        double a = this->stack.top(); \
        this->stack.pop();            \
        this->stack.push(a op b);     \
    } while (false)

    while (true) {
#ifdef DEBUG_TRACE_EXECUTION
        std::cout << "          ";
        printStack();
        disassembleInstruction(*this->chunk_, (int)(this->ip - this->chunk_->code.data()));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OpCode::OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                this->stack.push(constant);
                printValue(constant);
                std::cout << "\n";
                break;
            }
            case OpCode::OP_CONSTANT_LONG: {
                Value constant = READ_CONSTANT_LONG();
                this->stack.push(constant);
                printValue(constant);
                std::cout << "\n";
                break;
            }
            case OpCode::OP_ADD: {
                BINARY_OP(+);
                break;
            }
            case OpCode::OP_SUBTRACT: {
                BINARY_OP(-);
                break;
            }
            case OpCode::OP_MULTIPLY: {
                BINARY_OP(*);
                break;
            }
            case OpCode::OP_DIVIDE: {
                BINARY_OP(/);
                break;
            }
            case OpCode::OP_NEGATE: {
                stack.top() = -stack.top();
                break;
            }
            case OpCode::OP_RETURN: {
                printValue(this->stack.top());
                std::cout << "\n";
                this->stack.pop();
                return InterpretResult::INTERPRET_OK;
            }
        }
    }
#undef BINARY_OP
}

InterpretResult VM::interpret(Chunk *chunk) {
    this->chunk_ = chunk;
    this->ip = this->chunk_->code.data();
    return run();
}

InterpretResult VM::interpret(const std::string &source) {
    compile(source);

    return InterpretResult::INTERPRET_OK;
}


void VM::freeVM() {

}

void VM::printStack() const {
    auto st_copy = this->stack;

    std::cout << "[";

    while (!st_copy.empty()) {
        if (st_copy.size() == 1) {
            std::cout << st_copy.top();
        } else {
            std::cout << st_copy.top() << ", ";
        }
        st_copy.pop();
    }

    std::cout << "]\n";
}

void VM::resetStack() {
    this->stack = std::stack<Value>{};
}

constexpr uint8_t VM::READ_BYTE() {
    return (*this->ip++);
}

constexpr Value VM::READ_CONSTANT() {
    return this->chunk_->constants[READ_BYTE()];
}

constexpr Value VM::READ_CONSTANT_LONG() {
    const uint8_t constant_1byte = READ_BYTE();
    const uint8_t constant_2byte = READ_BYTE();
    const uint8_t constant_3byte = READ_BYTE();

    size_t index {0};
    index = (index) | constant_3byte;
    index = (index << 8) | constant_2byte;
    index = (index << 8) | constant_1byte;

    return this->chunk_->constants[index];
}
