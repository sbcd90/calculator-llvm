#include "parser.h"
#include <iostream>

namespace mycalc {
    namespace parser {
        ast::AnyExpr MyCalcParser::parse(const std::string &src) const {
            std::cout << "hit" << std::endl;
            return {};
        }
    }
}