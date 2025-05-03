#include "chunk.hpp"

Chunk::Chunk() {
  this->code = std::vector<uint8_t>{};
  this->constants = std::vector<Value>{};
  this->lines = std::vector<int>{};
}

Chunk::~Chunk() {
    freeChunk();
}


void Chunk::writeChunk(uint8_t byte, int line) {
  code.push_back(byte);
  lines.push_back(line);
}

void Chunk::freeChunk() {
  code = std::vector<uint8_t>{};
  constants = std::vector<Value>{};
  lines = std::vector<int>{};
}

size_t Chunk::count() const { return this->code.size(); }

void Chunk::writeConstant(Value value, int line) {
  size_t constant = this->addConstant(value);

  if (constant <= 255) {
    this->writeChunk(static_cast<uint8_t>(OpCode::OP_CONSTANT), line);
    this->writeChunk(constant, line);
  } else {
    this->writeChunk(static_cast<uint8_t>(OpCode::OP_CONSTANT_LONG), line);
    this->writeChunk(constant & 0xFF, line);
    this->writeChunk((constant >> 8) & 0xFF, line);
    this->writeChunk((constant >> 16) & 0xFF, line);
  }
}

size_t Chunk::addConstant(Value value) {
  this->constants.push_back(value);
  return this->constants.size() - 1;
}
