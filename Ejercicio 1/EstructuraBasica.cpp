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
    };

