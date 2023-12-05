#include <map>
#include <string>
#include <iostream>
#include <variant>

using namespace std;

class Environment {
public:
    Environment() {}

    ~Environment() {}

    using SymbolValue = variant<int, double, string>;

    void addSymbol(const string name, SymbolValue &value) {
        symbolTable[name] = value;
    }

    SymbolValue getSymbolValue(const string &name) {
        if (symbolTable.find(name) != symbolTable.end()) {
            return symbolTable[name];
        } else {
            cerr << "Error: Symbol '" << name << "' no encontrado en el Environment." << endl;
            return SymbolValue();
        }
    }

private;
    map<string, SymbolValue> symbolTable;
};

int main() {
    Environment env;

    env.addSymbol("x", 23);
    env.addSymbol("y", 43.7);
    env.addSymbol("nombre", "Juan Pablo");
}
