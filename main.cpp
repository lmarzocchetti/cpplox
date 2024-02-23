#include "chunk.hpp"
#include "debug.hpp"

int main() {
    Chunk chunk = Chunk();
    chunk.writeChunk(OpCode::OP_RETURN);

    disassembleChunk(chunk, "test chunk");

    chunk.freeChunk();

    return 0;
}
