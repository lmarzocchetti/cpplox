//
// Created by Lorenzo Marzocchetti on 24/02/24.
//

#ifndef CPPLOX_CHUNK_HPP
#define CPPLOX_CHUNK_HPP

#include <iostream>
#include <format>
#include <vector>

#include "common.hpp"
#include "value.hpp"

enum OpCode {
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN,
};

struct Chunk {
    std::vector<uint8_t> code;
    std::vector<int> lines;
    std::vector<Value> constants;

    Chunk();

    void writeChunk(uint8_t byte, int line);
    void freeChunk();
    void writeConstant(Value value, int line);
    size_t addConstant(Value value);

    [[nodiscard]] size_t count() const;
};

#endif //CPPLOX_CHUNK_HPP
