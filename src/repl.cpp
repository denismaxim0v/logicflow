#include "repl.h"
#include "lexer.h"
#include "parser.h"
#include "printer.h"

#include <iostream>
#include <string>
#include <vector>

void print_tokens(const std::vector<Token> &tokens) {
  for (const auto &token : tokens) {
    std::cout << "Token { ";
    switch (token.type) {
    case TokenType::Identifier:
      std::cout << "Identifier";
      break;
    case TokenType::Not:
      std::cout << "Not";
      break;
    case TokenType::And:
      std::cout << "And";
      break;
    case TokenType::Or:
      std::cout << "Or";
      break;
    case TokenType::Xor:
      std::cout << "Xor";
      break;
    case TokenType::LeftParen:
      std::cout << "LeftParen";
      break;
    case TokenType::RightParen:
      std::cout << "RightParen";
      break;
    case TokenType::Unknown:
      std::cout << "Unknown";
      break;
    case TokenType::Eof:
      std::cout << "Eof";
      break;
    };
    std::cout << " , " << token.val << " }\n";
  }
  std::cout << "\n";
}

void start_repl() {

  std::string line;
  std::cout << ">> ";

  while (std::getline(std::cin, line)) {
    if (line == "quit")
      break;

    Lexer lexer = Lexer(line);
    auto tokens = lexer.tokenize();

    print_tokens(tokens);

    Parser parser = Parser(tokens);
    auto ast = parser.parse();

    print_tree(*ast);
    std::cout << "\n>> ";
  }
};
