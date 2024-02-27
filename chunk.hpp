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

/**
 * Op Codes for the VM
 */
enum OpCode {
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
};

/**
 * Structure that define a chunk of code in the VM execution
 */
struct Chunk {
    std::vector<uint8_t> code;
    std::vector<int> lines;
    std::vector<Value> constants;

    Chunk();

    /**
     * Store a byte in the code vector and an int that represent a line in the line vector
     * @param byte: Can be an OpCode or operand to the related OpCode
     * @param line: Line number in the source code of the language
     */
    void writeChunk(uint8_t byte, int line);

    /**
     * Free all memory in the structure, so basically reinitialize the three vectors
     */
    void freeChunk();

    /**
     * Write an OpCode based on how many values are stored in the constants vector:
     * if there are less or equal 255 then use the OP_CONSTANT OpCode and 1 byte to store the position in the constant array.
     * if there are more than 255 elements in the constants array, use the OP_CONSTANT_LONG OpCode and 3 bytes.
     * @param value: Constant that we want to save in the constant vector
     * @param line: Line number in the source code of the language
     */
    void writeConstant(Value value, int line);

    /**
     * Store a value in the constants array, without writing OpCode. Used most for internal behaviour.
     * @param value: Value to store
     * @return: The position in the constants array
     */
    size_t addConstant(Value value);

    /**
     * Return the number of elements in the code vector
     * @return: Number of elements in the code vector
     */
    [[nodiscard]] size_t count() const;
};

#endif //CPPLOX_CHUNK_HPP
