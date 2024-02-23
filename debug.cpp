//
// Created by Lorenzo Marzocchetti on 23/02/24.
//

#include "debug.hpp"

void disassembleChunk(const Chunk& chunk, const std::string& name) {
    std::cout << std::format("== {} ==\n", name);

    for (int offset = 0; offset < chunk.count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const std::string& name, int offset) {
    std::cout << std::format("{}\n", name);
    return offset + 1;
}

int disassembleInstruction(const Chunk& chunk, int offset) {
    std::cout << std::format("{:04} ", offset);

    uint8_t instruction = chunk.code[offset];

    switch (instruction) {
        case OpCode::OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            std::cout << std::format("Unknown opcode {}\n", instruction);
            return offset + 1;
    }
}