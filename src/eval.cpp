#include "eval.h"
#include <stdexcept>

bool lookup(const std::string &name, const std::vector<std::string> &vars,
            const std::vector<bool> &values) {
  for (size_t i = 0; i < vars.size(); ++i)
    if (vars[i] == name)
      return values[i];

  throw std::runtime_error("Unknown var");
};

bool eval_expr(int id, const Expressions &expressions,
               const std::vector<std::string> &vars,
               const std::vector<bool> &values) {
  const Expr &e = expressions.nodes[id];

  if (e.kind == ExprKind::Identifier) {
    return lookup(e.name, vars, values);
  }

  if (e.kind == ExprKind::Unary) {
    return !eval_expr(e.rhs, expressions, vars, values);
  }

  if (e.kind == ExprKind::Binary) {
    bool l = eval_expr(e.lhs, expressions, vars, values);
    bool r = eval_expr(e.rhs, expressions, vars, values);

    if (e.op == '&')
      return l && r;
    if (e.op == '|')
      return l || r;
    if (e.op == '^')
      return l ^ r;
  }

  throw std::runtime_error("Invalid expression");
};
