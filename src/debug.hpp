#pragma once

#include "chunk.hpp"

/**
 * Disassemble a Chunk, printing the OpCodes, parameters and result of the instructions
 * @param chunk: const reference to the Chunk structure we want to disassemble
 * @param name: name of the specific Chunk
 */
void disassembleChunk(const Chunk& chunk, const std::string& name);

/**
 * Disassemble an instruction, printing the OpCodes, parameters and result of the instructions
 * @param chunk: const reference to the Chunk structure we want to disassemble
 * @param offset: Offset of the instruction in the VM program (basically the program counter)
 * @return
 */
int disassembleInstruction(const Chunk& chunk, int offset);
