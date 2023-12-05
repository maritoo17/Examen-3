#include <map>
#include <string>
#include <iostream>

class Environment {
public:
    Environment() {}
    ~Environment() {}

    enum class ValueType { INT, DOUBLE, STRING };
    struct SymbolValue {
        ValueType type;
        union {
            int intValue;
            double doubleValue;
            std::string* stringValue;
        };

        SymbolValue() : type(ValueType::INT), intValue(0) {}
        ~SymbolValue() {
            if (type == ValueType::STRING) delete stringValue;
        }
    };

    void addSymbol(const std::string& name, const SymbolValue& value) {
        symbolTable[name] = value;
    }

    SymbolValue getSymbolValue(const std::string& name) {
        if (symbolTable.find(name) != symbolTable.end()) {
            return symbolTable[name];
        } else {
            std::cerr << "Error: Symbol '" << name << "' no encontrado en el Environment." << std::endl;
            return SymbolValue();
        }
    }

    bool insert(const std::string& name, const SymbolValue& value) {
        auto it = symbolTable.find(name);
        if (it == symbolTable.end()) {
            symbolTable[name] = value;
            return true;
        } else {
            std::cerr << "Error: Symbol '" << name << "' ya existe en el Environment." << std::endl;
            return false;
        }
    }

private:
    std::map<std::string, SymbolValue> symbolTable;
};

int main() {
    Environment env;

    Environment::SymbolValue x;
    x.type = Environment::ValueType::INT;
    x.intValue = 37;
    env.addSymbol("x", x);

    Environment::SymbolValue y;
    y.type = Environment::ValueType::DOUBLE;
    y.doubleValue = 36.7;
    env.addSymbol("y", y);

    Environment::SymbolValue name;
    name.type = Environment::ValueType::STRING;
    name.stringValue = new std::string("Juan Pablo");
    env.addSymbol("nombre", name);

    auto valueX = env.getSymbolValue("x");
    auto valueY = env.getSymbolValue("y");
    auto valueName = env.getSymbolValue("nombre");

    if (valueX.type == Environment::ValueType::INT) {
        std::cout << "Valor de x: " << valueX.intValue << std::endl;
    }

    if (valueY.type == Environment::ValueType::DOUBLE) {
        std::cout << "Valor de y: " << valueY.doubleValue << std::endl;
    }

    if (valueName.type == Environment::ValueType::STRING) {
        std::cout << "Nombre: " << *(valueName.stringValue) << std::endl;
    }

    Environment::SymbolValue z;
    z.type = Environment::ValueType::INT;
    z.intValue = 50;
    env.insert("z", z);

    Environment::SymbolValue nombre;
    nombre.type = Environment::ValueType::STRING;
    nombre.stringValue = new std::string("Maria");
    env.insert("nombre", nombre);


    return 0;
}
