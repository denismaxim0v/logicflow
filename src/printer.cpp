#include "printer.h"
#include <iostream>
#include <variant>

static void print_expr(const Expr &expr, const std::string &indent,
                       bool is_last) {
  std::cout << indent;
  if (!indent.empty()) {
    std::cout << (is_last ? "└── " : "├── ");
  }

  if (std::holds_alternative<IdentifierExpr>(expr.node)) {
    const auto &id = std::get<IdentifierExpr>(expr.node);
    std::cout << "Identifier(" << id.name << ")\n";
    return;
  }

  if (std::holds_alternative<UnaryExpr>(expr.node)) {
    const auto &un = std::get<UnaryExpr>(expr.node);
    std::cout << "Unary(" << un.name << ")\n";

    print_expr(*un.rhs, indent + (is_last ? "    " : "│   "), true);
    return;
  }

  if (std::holds_alternative<BinaryExpr>(expr.node)) {
    const auto &bin = std::get<BinaryExpr>(expr.node);
    std::cout << "Binary(" << bin.op << ")\n";

    print_expr(*bin.left, indent + (is_last ? "    " : "│   "), false);
    print_expr(*bin.right, indent + (is_last ? "    " : "│   "), true);
    return;
  }
}

void print_tree(const Expr &expr) { print_expr(expr, "", true); }
