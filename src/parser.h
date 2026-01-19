#pragma once

#include "lexer.h"
#include <memory>
#include <string>
#include <variant>

struct Expr;

struct IdentifierExpr {
  std::string name;
};

struct UnaryExpr {
  std::string name;
  std::unique_ptr<Expr> rhs;
};

struct BinaryExpr {
  std::string op;
  std::unique_ptr<Expr> left;
  std::unique_ptr<Expr> right;
};

struct Expr {
  using Node = std::variant<IdentifierExpr, UnaryExpr, BinaryExpr>;
  Node node;

  template <typename T> explicit Expr(T value) : node(std::move(value)) {}
};

class Parser {
public:
  explicit Parser(std::vector<Token> tokens);

  std::unique_ptr<Expr> parse();

private:
  const Token &peek() const;
  const Token &advance();

  bool match(TokenType type);

  std::unique_ptr<Expr> parse_expr(int min_bp);
  std::unique_ptr<Expr> parse_prefix();

  int infix_binding_power(TokenType type) const;

  std::vector<Token> tokens;
  size_t pos = 0;
};
