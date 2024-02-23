//
// Created by Lorenzo Marzocchetti on 23/02/24.
//

#ifndef CPPLOX_DEBUG_HPP
#define CPPLOX_DEBUG_HPP

#include "chunk.hpp"

void disassembleChunk(const Chunk& chunk, const std::string& name);
int disassembleInstruction(const Chunk& chunk, int offset);

#endif //CPPLOX_DEBUG_HPP
