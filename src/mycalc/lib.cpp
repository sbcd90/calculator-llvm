#include "lib.h"
#include "ast/ast.h"
#include "parser.h"
#include "codegen.h"
#include "semantics/type_checker.h"

#include <boost/variant/apply_visitor.hpp>

#include <string>
#include <memory>
#include <iostream>

namespace mycalc {
    std::string parseAndStringize(const std::string &src) {

    }

    void parseAndCodegen(const std::string &src, codegen::LLVMCodeGenerator &gen) {

    }

    ast::AnyExpr parse(const std::string &src) {

    }
}