#include "parser.h"
#include <stdexcept>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {};

const Token &Parser::peek() const { return tokens[pos]; };

const Token &Parser::advance() { return tokens[pos++]; }

bool Parser::match(TokenType type) {
  if (peek().type == type) {
    advance();
    return true;
  }

  return false;
}

std::unique_ptr<Expr> Parser::parse() {
  auto expr = parse_expr(0);

  if (peek().type != TokenType::Eof) {
    throw std::runtime_error("Unexpected token");
  }

  return expr;
}

std::unique_ptr<Expr> Parser::parse_expr(int min_bp) {
  auto lhs = parse_prefix();

  while (true) {
    TokenType op = peek().type;

    int bp = infix_binding_power(op);

    if (bp < min_bp)
      break;

    Token op_c = advance();
    int next_min_bp = bp + 1;

    auto rhs = parse_expr(next_min_bp);

    lhs = std::make_unique<Expr>(
        BinaryExpr{std::string(op_c.val), std::move(lhs), std::move(rhs)});
  }

  return lhs;
};

std::unique_ptr<Expr> Parser::parse_prefix() {
  Token tok = advance();

  switch (tok.type) {
  case TokenType::Identifier:
    return std::make_unique<Expr>(IdentifierExpr{std::string(tok.val)});

  case TokenType::Not: {
    auto rhs = parse_expr(70);
    return std::make_unique<Expr>(UnaryExpr{"!", std::move(rhs)});
  }
  case TokenType::LeftParen: {
    auto expr = parse_expr(0);
    if (!match(TokenType::RightParen)) {
      throw std::runtime_error("Expected closing paren");
    }

    return expr;
  }
  default:
    throw std::runtime_error("Unexpected token.");
  }
}

int Parser::infix_binding_power(TokenType type) const {
  switch (type) {
  case TokenType::And:
    return 60;
  case TokenType::Xor:
    return 50;
  case TokenType::Or:
    return 40;
  default:
    return -1;
  }
}
