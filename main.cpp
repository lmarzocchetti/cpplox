#include <fstream>

#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"

static void repl(VM& vm) {
    std::string line{};

    while (true) {
        if (!std::getline(std::cin, line)) {
            printf("exiting...\n");
            break;
        }

        vm.interpret(line);
    }
}

static std::string readFile(const std::string& path) {
    std::string buffer;

    std::ifstream input{path};
    if (!input) {
        std::cerr << "Cannot open file " << path << "\n";
        exit(74);
    }

    input.seekg(0, std::ios::end);
    buffer.resize(input.tellg());
    input.seekg(0);
    input.read(buffer.data(), buffer.size());

    return buffer;
}

static void runFile(VM& vm, const std::string& path) {
    std::string source = readFile(path);

    std::cout << source << std::endl;

    InterpretResult result = vm.interpret(source);

    if (result == InterpretResult::INTERPRET_COMPILE_ERROR) {
        exit(65);
    }
    if (result == InterpretResult::INTERPRET_RUNTIME_ERROR) {
        exit(70);
    }
}

int main1() {
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

int main(int argc, const char* argv[]) {
    VM vm = VM();

    if (argc == 1) {
        repl(vm);
    } else if (argc == 2) {
        runFile(vm, argv[1]);
    }
    else {
        std::cerr << "Usage: cpplox [path]\n";
        exit(64);
    }

    vm.freeVM();
    return 0;
}
