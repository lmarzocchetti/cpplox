//
// Created by Lorenzo Marzocchetti on 03/03/24.
//

#ifndef CPPLOX_SCANNER_HPP
#define CPPLOX_SCANNER_HPP

#include <iostream>

enum TokenType {
    // Single-character tokens.
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,

    // One or two character tokens
    TOKEN_BANG, TOKEN_BANG_EQUAL,
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER, TOKEN_GREATER_EQUAL,
    TOKEN_LESS, TOKEN_LESS_EQUAL,

    // Literals
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,

    // Keywords
    TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NUL, TOKEN_OR,
    TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
    TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,

    TOKEN_ERROR, TOKEN_EOF
};

struct Token {
    TokenType type;
    std::string start;
    int length;
    int line;

    Token(TokenType type, const std::string& start, int length, int line);
};

struct Scanner {
    std::string source;
    int current;
    int line;

    Scanner(const std::string& source);

    Token scanToken();
private:
    bool isAtEnd();
    char advance();
    char peek();
    char peekNext();
    bool match(char expected);

    void skipWhitespace();

    Token makeToken(TokenType type);
    Token errorToken(const std::string& message);
};

#endif //CPPLOX_SCANNER_HPP
