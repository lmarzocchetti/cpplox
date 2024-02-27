#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"

int main() {
    VM vm = VM();

    Chunk chunk = Chunk();

    for (int i = 0; i < 270; i++) {
        chunk.writeConstant(1.2, i);
    }

    chunk.writeChunk(OpCode::OP_RETURN, 123);
    // disassembleChunk(chunk, "test chunk");

    vm.interpret(&chunk);

    vm.freeVM();
    chunk.freeChunk();

    return 0;
}
