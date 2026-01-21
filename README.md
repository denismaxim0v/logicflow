# Boolean Logic Parser & Truth Table Generator
A small boolean logic language implemented in C++ featuring:

- a hand-written lexer
- a Pratt parser
- expression evaluation
- truth table generation

## Example
Input expression
```
A | B & !C
```

Output:
```
A B C | result
0 0 0 | 0
0 0 1 | 0
0 1 0 | 1
0 1 1 | 0
1 0 0 | 1
1 0 1 | 1
1 1 0 | 1
1 1 1 | 1
```

## Build steps
```
mkdir build
cd build
cmake ..
cmake --build .
./LogicInterp
```
