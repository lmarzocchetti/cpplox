//
// Created by Lorenzo Marzocchetti on 24/02/24.
//
//

#include "chunk.hpp"

Chunk::Chunk() {
    this->code = std::vector<uint8_t>{};
    this->constants = std::vector<Value>{};
}

void Chunk::writeChunk(uint8_t byte) {
    code.push_back(byte);
}

void Chunk::freeChunk() {
    code = std::vector<uint8_t>{};
}

size_t Chunk::count() const {
    return this->code.size();
}