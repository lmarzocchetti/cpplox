//
// Created by Lorenzo Marzocchetti on 03/03/24.
//

#include "compiler.hpp"

void compile(const std::string& source) {
    Scanner scanner = Scanner(source);

    int line = -1;

    while (true) {
        Token token = scanner.scanToken();
        if (token.line != line) {
            std::cout << std::format("line: {}\n", token.line);
            line = token.line;
        }

        std::cout << "      | ";
        std::cout << std::format("{} '{}'\n", static_cast<uint8_t>(token.type), token.start);

        if (token.type == TokenType::TOKEN_EOF) {
            break;
        }
    }
}
