#pragma once

#include "parser.h"
#include <string>
#include <unordered_map>

bool eval_expr(
  int expr_id,
  const Expressions& expressions,
  const std::vector<std::string>& vars,
  const std::vector<bool>& values
);
