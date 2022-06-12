#ifndef MYCALC_PARSER_H_
#define MYCALC_PARSER_H_

#include <string>
#include <memory>

#include "ast/ast.h"

namespace mycalc {
    namespace parser {
        class MyCalcParser final {
        public:
            ast::AnyExpr parse(std::string const& src) const;
        };
    }
}

#endif // MYCALC_PARSER_H_