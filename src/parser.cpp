#include "parser.h"
#include <stdexcept>

Parser::Parser(std::vector<Token> t, Expressions &e)
    : tokens(t), expressions(e) {};

const Token &Parser::peek() const { return tokens[pos]; };

const Token &Parser::advance() { return tokens[pos++]; }

bool Parser::match(TokenType type) {
  if (peek().type == type) {
    advance();
    return true;
  }

  return false;
}

int Parser::parse() {
  auto expr = parse_expr(0);

  if (peek().type != TokenType::Eof) {
    throw std::runtime_error("Unexpected token");
  }

  return expr;
}

int Parser::parse_expr(int min_bp) {
  auto lhs = parse_prefix();

  while (true) {
    TokenType op = peek().type;

    int bp = infix_binding_power(op);

    if (bp < min_bp)
      break;

    Token op_c = advance();
    int next_min_bp = bp + 1;

    auto rhs = parse_expr(next_min_bp);

    lhs = expressions.add(Expr{
        .kind = ExprKind::Binary, .op = op_c.val[0], .lhs = lhs, .rhs = rhs});
  }

  return lhs;
};

int Parser::parse_prefix() {
  Token tok = advance();

  if (tok.type == TokenType::Identifier) {
    return expressions.add(
        Expr{.kind = ExprKind::Identifier, .name = std::string(tok.val)});
  }

  if (tok.type == TokenType::Not) {
    int rhs = parse_expr(70);
    return expressions.add(
        Expr{.kind = ExprKind::Unary, .op = '!', .rhs = rhs});
  }

  if (tok.type == TokenType::LeftParen) {
    int expr = parse_expr(0);
    if (!match(TokenType::RightParen))
      throw std::runtime_error("Expected ')'");
    return expr;
  }

  throw std::runtime_error("Unexpected token");
}

int Parser::infix_binding_power(TokenType type) const {
  if (type == TokenType::And)
    return 60;
  if (type == TokenType::Xor)
    return 50;
  if (type == TokenType::Or)
    return 40;
  return -1;
}
