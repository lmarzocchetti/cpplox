//
// Created by Lorenzo Marzocchetti on 03/03/24.
//

#include "scanner.hpp"

// TOKEN

Token::Token(TokenType type, const std::string& start, int length, int line) {
    this->type = type;
    this->start = start;
    this->length = length;
    this->line = line;
}

// TOKEN

// SCANNER

Scanner::Scanner(const std::string& source) {
    this->source = source;
    this->current = 0;
    this->line = 1;
}

Token Scanner::scanToken() {
    //scanner.start = scanner.current
    skipWhitespace();

    if (isAtEnd()) {
        return makeToken(TokenType::TOKEN_EOF);
    }

    char c = advance();

    switch (c) {
        case '(':
            return makeToken(TokenType::TOKEN_LEFT_PAREN);
        case ')':
            return makeToken(TokenType::TOKEN_RIGHT_PAREN);
        case '{':
            return makeToken(TokenType::TOKEN_LEFT_BRACE);
        case '}':
            return makeToken(TokenType::TOKEN_RIGHT_BRACE);
        case ';':
            return makeToken(TokenType::TOKEN_SEMICOLON);
        case ',':
            return makeToken(TokenType::TOKEN_COMMA);
        case '.':
            return makeToken(TokenType::TOKEN_DOT);
        case '-':
            return makeToken(TokenType::TOKEN_MINUS);
        case '+':
            return makeToken(TokenType::TOKEN_PLUS);
        case '/':
            return makeToken(TokenType::TOKEN_SLASH);
        case '*':
            return makeToken(TokenType::TOKEN_STAR);
        case '!':
            return makeToken(match('=') ? TokenType::TOKEN_BANG_EQUAL : TokenType::TOKEN_BANG);
        case '=':
            return makeToken(match('=') ? TokenType::TOKEN_EQUAL_EQUAL : TokenType::TOKEN_EQUAL);
        case '<':
            return makeToken(match('=') ? TokenType::TOKEN_LESS_EQUAL : TokenType::TOKEN_LESS);
        case '>':
            return makeToken(match('=') ? TokenType::TOKEN_GREATER_EQUAL : TokenType::TOKEN_GREATER);
    }

    return errorToken("Unexpected character.");
}

bool Scanner::isAtEnd() {
    return this->source.length() == this->current;
}

char Scanner::advance() {
    this->current += 1;
    return this->source[current-1];
}

char Scanner::peek() {
    return this->source[current];
}

char Scanner::peekNext() {
    if (isAtEnd()) {
        return '\0';
    }
    return this->source[current + 1];
}

bool Scanner::match(char expected) {
    if (isAtEnd()) {
        return false;
    }

    if (this->source[current] != expected) {
        return false;
    }

    this->current += 1;
    return true;
}

void Scanner::skipWhitespace() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                this->line += 1;
                advance();
                break;
            case '/':
                if (peekNext() == '/') {
                    while (peek() != '\n' && !isAtEnd()) {
                        advance();
                    }
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

Token Scanner::makeToken(TokenType type) {
    return Token{type, this->source, this->current, this->line};
}

Token Scanner::errorToken(const std::string& message) {
    return Token{TokenType::TOKEN_ERROR, message, static_cast<int>(message.length()), this->line};
}




// SCANNER