#pragma once

#include "lexer.h"
#include <memory>
#include <string>
#include <variant>

enum class ExprKind { Identifier, Unary, Binary };

struct Expr {
  ExprKind kind;

  std::string name;

  char op = 0;
  int lhs = -1;
  int rhs = -1;
};

struct Expressions {
  std::vector<Expr> nodes;

  int add(const Expr &e) {
    nodes.push_back(e);
    return (int)nodes.size() - 1;
  }
};

class Parser {
public:
  Parser(std::vector<Token> tokens, Expressions& expressions);
  int parse();

private:
  const Token &peek() const;
  const Token &advance();

  int parse_expr(int min_bp);
  int parse_prefix();

  bool match(TokenType type);
  int infix_binding_power(TokenType type) const;

  const std::vector<Token> tokens;
  size_t pos = 0;
  Expressions& expressions;
};
