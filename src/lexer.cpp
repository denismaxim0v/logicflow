#include "lexer.h"

// HELPERS
bool is_operator(char c) {
  return c == '!' || c == '&' || c == '|' || c == '^';
}

// LEXER
Lexer::Lexer(std::string_view input) { src = input; }

char Lexer::peek() const { return is_end() ? '\0' : src[curr]; }

char Lexer::advance() {
  const auto c = peek();
  ++curr;
  return c;
}

bool Lexer::is_end() const { return curr >= src.size(); }

void Lexer::skip_whitespace() {
  while (!is_end()) {
    char c = peek();
    if (isspace(c)) {
      advance();
    } else {
      break;
    }
  }
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;

  while (!is_end()) {
    skip_whitespace();
    if (is_end()) break;
    char c = peek();

    if (isalpha(c)) {
      Token ident = read_identifier();
      tokens.push_back(ident);
    } else if (is_operator(c)) {
      Token op = read_operator();
      tokens.push_back(op);
    } else {
      Token symbol = read_symbol();
      tokens.push_back(symbol);
    }
  }

  tokens.push_back(Token{.val = "", .type = TokenType::Eof});

  return tokens;
}

Token Lexer::read_identifier() {
  size_t start = curr;

  while (isalnum(peek()) || peek() == '_') {
    advance();
  }

  auto ident = src.substr(start, curr - start);

  return Token{.val = ident, .type = TokenType::Identifier};
}

Token Lexer::read_operator() {
  char c = advance();

  if (c == '!') {
    return Token{.val = "!", .type = TokenType::Not};
  } else if (c == '&') {
    return Token{.val = "&", .type = TokenType::And};
  } else if (c == '|') {
    return Token{.val = "|", .type = TokenType::Or};
  } else if (c == '^') {
    return Token{.val = "^", .type = TokenType::Xor};
  } else {
    return Token{.val = "", .type = TokenType::Unknown};
  }
}

Token Lexer::read_symbol() {
  char c = advance();

  if (c == '(') {
    return Token{.val = "(", .type = TokenType::LeftParen};
  } else if (c == ')') {
    return Token{.val = ")", .type = TokenType::RightParen};
  } else {
    return Token{.val = "", .type = TokenType::Unknown};
  }
}
