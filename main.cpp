#include "Content/TokenBuilding.h"
#include "Content/Parser.h"

#include <iostream>
#include <fstream>

using namespace SimpleParser;

auto main() -> int
{
    std::cout << "Simple Parser Loading... \n\n" << std::endl;

    std::ifstream file("../test.myc");
    if (!file) {
        std::cerr << "Did not find the file." << std::endl;
        return 0;
    }
    std::string f_content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    TokenBuilding tokenBuilding;
    std::vector<Token> tokens = tokenBuilding.parse(f_content);

    Parser parser;
    parser.parse(tokens);

    parser.debugPrint();

    return 0;
}