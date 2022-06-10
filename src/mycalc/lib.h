#ifndef MYCALC_LIB_H_
#define MYCALC_LIB_H_

#include <string>
#include <memory>
#include "codegen.h"

namespace mycalc {
    std::string parseAndStringize(std::string const&);
    void parseAndCodegen(std::string const&, codegen::LLVMCodeGenerator&);
    ast::AnyExpr parse(std::string const&);
}

#endif // MYCALC_LIB_H_