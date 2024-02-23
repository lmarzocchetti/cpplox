//
// Created by Lorenzo Marzocchetti on 23/02/24.
//

#ifndef CPPLOX_CHUNK_HPP
#define CPPLOX_CHUNK_HPP

#include <iostream>
#include <format>

#include "common.hpp"
#include "memory.hpp"

enum OpCode {
    OP_RETURN,
};

struct Chunk {
    int count;
    int capacity;
    uint8_t* code;

    Chunk() {
        this->count = 0;
        this->capacity = 0;
        this->code = nullptr;
    }

    void freeChunk() {
        FREE_ARRAY(code, capacity);
        this->capacity = 0;
        this->count = 0;
    }

    void writeChunk(uint8_t byte) {
        if (capacity < count + 1) {
            int oldCapacity = capacity;
            capacity = GROW_CAPACITY(oldCapacity);
            code = GROW_ARRAY(code, oldCapacity, capacity);
        }

        code[count] = byte;
        count += 1;
    }
};

#endif //CPPLOX_CHUNK_HPP
