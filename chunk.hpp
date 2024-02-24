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
    OP_RETURN,
};

struct Chunk {
    std::vector<uint8_t> code;
    std::vector<Value> constants;

    Chunk();

    void writeChunk(uint8_t byte);
    void freeChunk();
    [[nodiscard]] size_t count() const;
};

#endif //CPPLOX_CHUNK_HPP
