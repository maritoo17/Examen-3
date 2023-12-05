#include <map>
#include <string>
#include <iostream>

class Environment {
public:
    Environment() {}

    ~Environment() {}

    enum class ValueType {INT, DOUBLE, STRING};
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

        void addSymbol(const std::string& name, const SymbolValue& value) {
            symbolTable[name] = value;
        }

        SymbolValue getSymbolValue(const std::string& name) {
            if (symbolTable.find(name) != symbolTable.end()) {
                return symbolTable[name];
            } else {
                std::cerr << "Error: Symbol '" << name << "' not found in the environment." << std::endl;
                return SymbolValue();
            }
        }

    private:
        std::map<std::string, SymbolValue> symbolTable;
    };
};



