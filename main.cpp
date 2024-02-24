#include "chunk.hpp"
#include "debug.hpp"

int main() {
    Chunk chunk = Chunk();

    for (int i = 0; i < 270; i++) {
        chunk.writeConstant(1.2, i);
    }

    chunk.writeChunk(OpCode::OP_RETURN, 123);

    disassembleChunk(chunk, "test chunk");

    chunk.freeChunk();

    return 0;
}
