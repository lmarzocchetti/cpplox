//
// Created by Lorenzo Marzocchetti on 23/02/24.
//

#include "debug.hpp"

void disassembleChunk(const Chunk& chunk, const std::string& name) {
    std::cout << std::format("== {} ==\n", name);

    for (int offset = 0; offset < chunk.count();) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int constantInstruction(const std::string& name, const Chunk& chunk, int offset) {
    uint8_t constant = chunk.code[offset + 1];
    std::cout << std::format("{}    {} '", name, constant);
    printValue(chunk.constants[constant]);
    std::cout << "'\n";
    return offset + 2;
}

static int constantLongInstruction(const std::string& name, const Chunk& chunk, int offset) {
    const uint8_t constant_1byte = chunk.code[offset + 1];
    const uint8_t constant_2byte = chunk.code[offset + 2];
    const uint8_t constant_3byte = chunk.code[offset + 3];

    size_t index {0};
    index = (index) | constant_3byte;
    index = (index << 8) | constant_2byte;
    index = (index << 8) | constant_1byte;

    std::cout << std::format("{}    {} '", name, index);
    printValue(chunk.constants[index]);
    std::cout << "'\n";

    return offset + 4;
}

static int simpleInstruction(const std::string& name, int offset) {
    std::cout << std::format("{}\n", name);
    return offset + 1;
}

int disassembleInstruction(const Chunk& chunk, int offset) {
    std::cout << std::format("{:04} ", offset);

    if (offset > 0 && chunk.lines[offset] == chunk.lines[offset - 1]) {
        std::cout << "   | ";
    } else {
        std::cout << std::format("{:04} ", chunk.lines[offset]);
    }

    uint8_t instruction = chunk.code[offset];

    switch (instruction) {
        case OpCode::OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OpCode::OP_CONSTANT_LONG:
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
        case OpCode::OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            std::cout << std::format("Unknown opcode {}\n", instruction);
            return offset + 1;
    }
}