//
// Created by Lorenzo Marzocchetti on 23/02/24.
//

#ifndef CPPLOX_MEMORY_HPP
#define CPPLOX_MEMORY_HPP

#include "common.hpp"

constexpr int GROW_CAPACITY(int capacity) {
    return capacity < 8 ? 8 : capacity * 2;
}

constexpr uint8_t* GROW_ARRAY(uint8_t* pointer, int oldSize, int newSize) {
    if (newSize == 0) {
        delete[] pointer;
        return nullptr;
    }

    auto* result = static_cast<uint8_t *>(realloc(pointer, newSize));

    if (result == nullptr) {
        exit(1);
    }

    return result;
}

constexpr void FREE_ARRAY(uint8_t* pointer, int capacity) {
    GROW_ARRAY(pointer, capacity, 0);
}

#endif //CPPLOX_MEMORY_HPP
