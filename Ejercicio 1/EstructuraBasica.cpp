#include <map>
#include <string>
#include <iostream>
#include <variant>

using namespace std;

class Environment {
public:
    Environment () {}

    ~Environment () {}

    using SymbolValue = variant<int , double, string>;

    void addSymbol (const string name, SymbolValue& value) {
        symbolTable[name] = value;
    }
};