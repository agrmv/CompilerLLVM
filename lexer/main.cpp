#include <memory>
#include <fstream>
#include "Lexer.h"

int main() {
    std::ifstream file;
    file.open("kotlin.kt",std::ios_base::in);
    auto lexer = std::make_unique<Lexer>(file, "kotlin.kt");
    lexer->tokenize();
    return 0;
}
/*
 * TODO:
 *  автотесты
 */