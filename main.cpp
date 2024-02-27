#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"

int main() {
    VM vm = VM();

    Chunk chunk = Chunk();

    chunk.writeConstant(1.2, 123);
    chunk.writeConstant(3.4, 123);

    chunk.writeChunk(OpCode::OP_ADD, 123);

    chunk.writeConstant(5.6, 123);
    chunk.writeChunk(OpCode::OP_DIVIDE, 123);
    chunk.writeChunk(OpCode::OP_NEGATE, 123);

    chunk.writeChunk(OpCode::OP_RETURN, 123);
    // disassembleChunk(chunk, "test chunk");

    vm.interpret(&chunk);

    vm.freeVM();
    chunk.freeChunk();

    return 0;
}
