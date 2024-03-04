//
// Created by Lorenzo Marzocchetti on 03/03/24.
//

#include "scanner.hpp"

// TOKEN

Token::Token(TokenType type, const std::string& start, int line) {
    this->type = type;
    this->start = start;
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
    this->tok_len = 1;

    //scanner.start = scanner.current

    skipWhitespace();

    if (isAtEnd()) {
        return makeToken(TokenType::TOKEN_EOF, false);
    }

    char c = advance();

    if (isAlpha(c)) {
        return identifier();
    }

    if (isDigit(c)) {
        return number();
    }

    switch (c) {
        case '(':
            return makeToken(TokenType::TOKEN_LEFT_PAREN, false);
        case ')':
            return makeToken(TokenType::TOKEN_RIGHT_PAREN, false);
        case '{':
            return makeToken(TokenType::TOKEN_LEFT_BRACE, false);
        case '}':
            return makeToken(TokenType::TOKEN_RIGHT_BRACE, false);
        case ';':
            return makeToken(TokenType::TOKEN_SEMICOLON, false);
        case ',':
            return makeToken(TokenType::TOKEN_COMMA, false);
        case '.':
            return makeToken(TokenType::TOKEN_DOT, false);
        case '-':
            return makeToken(TokenType::TOKEN_MINUS, false);
        case '+':
            return makeToken(TokenType::TOKEN_PLUS, false);
        case '/':
            return makeToken(TokenType::TOKEN_SLASH, false);
        case '*':
            return makeToken(TokenType::TOKEN_STAR, false);
        case '!':
            if (match('=')) {
                tok_len += 1;
                return makeToken(TokenType::TOKEN_BANG_EQUAL, true);
            }
            else {
                return makeToken(TokenType::TOKEN_BANG, false);
            }
        case '=':
            if (match('=')) {
                tok_len += 1;
                return makeToken(TokenType::TOKEN_EQUAL_EQUAL, true);
            }
            else {
                return makeToken(TokenType::TOKEN_EQUAL, false);
            }
        case '<':
            if (match('=')) {
                tok_len += 1;
                return makeToken(TokenType::TOKEN_LESS_EQUAL, true);
            }
            else {
                return makeToken(TokenType::TOKEN_LESS, false);
            }
        case '>':
            if (match('=')) {
                tok_len += 1;
                return makeToken(TokenType::TOKEN_GREATER_EQUAL, true);
            }
            else {
                return makeToken(TokenType::TOKEN_GREATER, false);
            }
        case '"':
            tok_len = 0;
            return string();
    }

    return errorToken("Unexpected character.");
}

bool Scanner::isAtEnd() const {
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

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
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

Token Scanner::string() {
    int starting = this->current;

    std::string str {};

    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            this->line += 1;
        }
        advance();
        tok_len += 1;
    }
    if (isAtEnd()) {
        return errorToken("Unterminated string.");
    }

    advance();
    return Token{TokenType::TOKEN_STRING, this->source.substr(starting, tok_len), this->line};
}

Token Scanner::number() {
    int starting = this->current - 1;

    while (isDigit(peek())) {
        advance();
        this->tok_len += 1;
    }

    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        this->tok_len += 1;

        while (isDigit(peek())) {
            advance();
            this->tok_len += 1;
        }
    }

    return Token{TokenType::TOKEN_NUMBER, this->source.substr(starting, tok_len), this->line};
}

TokenType Scanner::checkKeyword(int length, int skipped, const std::string& rest, TokenType type) {
    if (this->source.substr(this->current - length, length) == rest && skipped == length + 1) {
        return type;
    }

    return TokenType::TOKEN_IDENTIFIER;
}

TokenType Scanner::identifierType(int skipped) {
    switch (this->source[current - skipped]) {
        case 'a':
            return checkKeyword(2, skipped, "nd", TokenType::TOKEN_AND);
        case 'c':
            return checkKeyword(4, skipped, "lass", TokenType::TOKEN_CLASS);
        case 'e':
            return checkKeyword(3, skipped, "lse", TokenType::TOKEN_ELSE);
        case 'f':
            switch (this->source[current - skipped + 1]) {
                case 'a':
                    return checkKeyword(4, skipped, "alse", TokenType::TOKEN_FALSE);
                case 'o':
                    return checkKeyword(2, skipped, "or", TokenType::TOKEN_FOR);
                case 'u':
                    return checkKeyword(2, skipped, "un", TokenType::TOKEN_FUN);
            }
            break;
        case 'i':
            return checkKeyword(1, skipped, "f", TokenType::TOKEN_IF);
        case 'n':
            return checkKeyword(2, skipped, "il", TokenType::TOKEN_NIL);
        case 'o':
            return checkKeyword(1, skipped, "r", TokenType::TOKEN_OR);
        case 'p':
            return checkKeyword(4, skipped, "rint", TokenType::TOKEN_PRINT);
        case 'r':
            return checkKeyword(5, skipped, "eturn", TokenType::TOKEN_RETURN);
        case 's':
            return checkKeyword(4, skipped, "uper", TokenType::TOKEN_SUPER);
        case 't':
            switch (this->source[current - skipped + 1]) {
                case 'h':
                    return checkKeyword(3, skipped, "his", TokenType::TOKEN_THIS);
                case 'r':
                    return checkKeyword(3, skipped, "rue", TokenType::TOKEN_TRUE);
            }
            break;
        case 'v':
            return checkKeyword(2, skipped, "ar", TokenType::TOKEN_VAR);
        case 'w':
            return checkKeyword(4, skipped, "hile", TokenType::TOKEN_WHILE);
    }

    return TOKEN_IDENTIFIER;
}

Token Scanner::identifier() {
    int starting = this->current - 1;
    int skipped = 1;

    while (isAlpha(peek()) || isDigit(peek())) {
        advance();
        this->tok_len += 1;
        skipped += 1;
    }

    return Token{identifierType(skipped), this->source.substr(starting, tok_len), this->line};
}

Token Scanner::makeToken(TokenType type, bool matched) const {
    if (type == TokenType::TOKEN_EOF) {
        return Token{type, "", this->line};
    }

    if (matched) {
        return Token{type, this->source.substr(current - 2, tok_len), this->line};
    }

    return Token{type, this->source.substr(current - 1, tok_len), this->line};
}

Token Scanner::errorToken(const std::string& message) const {
    return Token{TokenType::TOKEN_ERROR, message, this->line};
}


// SCANNER