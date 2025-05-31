#include <iostream>
#include <string> 
#include <unordered_map>
#include <variant>
#include <memory>

enum class Type { 
    BOOL,
    CHAR,
    SIGNED_CHAR,
    UNSIGNED_CHAR,
    SHORT,
    UNSIGNED_SHORT,
    INT,
    UNSIGNED_INT,
    LONG,
    UNSIGNED_LONG,
    LONG_LONG,
    UNSIGNED_LONG_LONG,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE
};

using SymbolValue = std::variant<
    bool, char, signed char, unsigned char, short, unsigned short,
    int, unsigned int, long, unsigned long, long long, unsigned long long,
    float, double, long double
>;

struct Symbol {
    std::string name;
    Type type;
    SymbolValue value;
};

class SymbolTable {

private: 
    std::unordered_map<std::string, Symbol> symbols;

    static std::string typeToString(Type t) {
        switch (t) {
            case Type::CHAR: return "char";
            case Type::SIGNED_CHAR: return "signed char";
            case Type::UNSIGNED_CHAR: return "unsigned char";
            case Type::SHORT: return "short";
            case Type::UNSIGNED_SHORT: return "unsigned short";
            case Type::INT: return "int";
            case Type::UNSIGNED_INT: return "unsigned int";
            case Type::LONG: return "long";
            case Type::UNSIGNED_LONG: return "unsigned long";
            case Type::LONG_LONG: return "long long";
            case Type::UNSIGNED_LONG_LONG: return "unsigned long long";
            case Type::FLOAT: return "float";
            case Type::DOUBLE: return "double";
            case Type::LONG_DOUBLE: return "long double";
            case Type::BOOL: return "bool";
            default: return "unknown";
        }
    }

public:
    void addSymbol(const std::string& name, Type type, const SymbolValue& value) {
        symbols[name] = Symbol{name, type, value};
    }

    bool updateSymbol(const std::string& name, Type type, const SymbolValue& value) {
        auto it = symbols.find(name);
        if (it == symbols.end()) return false; 

        it->second.type = type;
        it->second.value = value;
        return true;
    }

    void printSymbol(const std::string& name) const {
        auto it = symbols.find(name);
        if (it == symbols.end()) {
            std::cout << "Symbol '" << name << "' not found.\n";
            return;
        }

        const Symbol& sym = it->second;
        std::cout << "Name: " << sym.name << " Type: " << typeToString(sym.type) << " Value: ";

        std::visit([](const auto& val) { std::cout << val; }, sym.value);
        std::cout << '\n';
    }
};

int main() {

    SymbolTable table;
    std::cout << "Adding symbol using temporary variable:\n";
    table.addSymbol("myCSOPESYGrade", Type::INT, 100);
    table.printSymbol("myCSOPESYGrade");

    std::cout << "\nUsing unique pointer to SymbolTable:\n";

    std::unique_ptr<SymbolTable> tablePtr = std::make_unique<SymbolTable>();
    tablePtr->addSymbol("myCSOPESYGrade", Type::INT, 100);
    tablePtr->printSymbol("myCSOPESYGrade");

}