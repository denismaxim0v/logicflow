#pragma once

#include <string>
#include <optional>
#include <vector>

enum class TokenType {
  Identifier,
  Not,
  And,
  Or,
  Xor,
  LeftParen,
  RightParen,
  Unknown,
  Eof,
};

struct Token {
  std::string_view val;
  TokenType type;
};

class Lexer {
public:
  Lexer(std::string_view input);

  std::vector<Token> tokenize();

private:
  std::string_view src;

  size_t start = 0;
  size_t curr = 0;

  bool is_end() const;
  char peek() const;

  char advance();
  void skip_whitespace();

  Token read_operator();
  Token read_symbol();
  Token read_identifier();
};
