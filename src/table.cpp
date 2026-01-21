#include "table.h"
#include "eval.h"
#include <iostream>
#include <set>
#include <vector>

static void collect_vars(int id, const Expressions &expressions,
                         std::set<std::string> &vars) {
  const Expr &e = expressions.nodes[id];

  if (e.kind == ExprKind::Identifier) {
    vars.insert(e.name);
  } else if (e.kind == ExprKind::Unary) {
    collect_vars(e.rhs, expressions, vars);
  } else if (e.kind == ExprKind::Binary) {
    collect_vars(e.lhs, expressions, vars);
    collect_vars(e.rhs, expressions, vars);
  }
}

void print_truth_table(int root, const Expressions &expressions) {
  std::set<std::string> var_set;
  collect_vars(root, expressions, var_set);

  std::vector<std::string> vars(var_set.begin(), var_set.end());
  int n = (int)vars.size();

  for (auto &v : vars)
    std::cout << v << " ";
  std::cout << "| result\n";

  int rows = 1 << n;
  for (int mask = 0; mask < rows; ++mask) {
    std::vector<bool> values(n);

    for (int i = 0; i < n; ++i) {
      values[i] = (mask & (1 << (n - i - 1))) != 0;
      std::cout << values[i] << " ";
    }

    bool result = eval_expr(root, expressions, vars, values);
    std::cout << "| " << result << "\n";
  }
}
