#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

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
        auto it = symbolTable.find(name);
        if (it != symbolTable.end()) {
            if (it->second.type != value.type) {
                throw std::invalid_argument("Error: Intentando insertar símbolo con tipo de valor diferente.");
            }
        }
        symbolTable[name] = value;
    }

    SymbolValue getSymbolValue(const std::string& name) {
        auto it = symbolTable.find(name);
        if (it != symbolTable.end()) {
            return it->second;
        } else {
            throw std::out_of_range("Error: Symbol no encontrado en el Environment.");
        }
    }

    bool insert(const std::string& name, const SymbolValue& value) {
        try {
            addSymbol(name, value);
            return true;
        } catch(const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    SymbolValue lookup(const std::string& name) {
        auto it = symbolTable.find(name);
        if (it != symbolTable.end()) {
            return it->second;
        } else {
            std::cerr << "Error: Symbol '" << name << "' no encontrado en el Environment." << std::endl;
            return SymbolValue();
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
    nombre.stringValue = new std::string("Jose María");
    env.insert("nombre", nombre);

    auto valueZ = env.lookup("z");
    if (valueZ.type == Environment::ValueType::INT) {
        std::cout << "Valor de z: " << valueZ.intValue << std::endl;
    }

    auto valueNotFound = env.lookup("no_encontrado");

    return 0;
}
