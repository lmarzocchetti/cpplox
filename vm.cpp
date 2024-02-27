//
// Created by Lorenzo Marzocchetti on 27/02/24.
//

#include "vm.hpp"

VM::VM() {

}

InterpretResult VM::run() {
    while (true) {
#ifdef DEBUG_TRACE_EXECUTION
        disassembleInstruction(*this->chunk_, (int)(this->ip - this->chunk_->code.data()));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OpCode::OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                printValue(constant);
                std::cout << "\n";
                break;
            }
            case OpCode::OP_CONSTANT_LONG: {
                Value constant = READ_CONSTANT_LONG();
                printValue(constant);
                std::cout << "\n";
                break;
            }
            case OpCode::OP_RETURN: {
                return InterpretResult::INTERPRET_OK;
            }
        }
    }
}

InterpretResult VM::interpret(Chunk *chunk) {
    this->chunk_ = chunk;
    this->ip = this->chunk_->code.data();
    return run();
}

void VM::freeVM() {

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
