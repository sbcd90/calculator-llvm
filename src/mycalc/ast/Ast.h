#ifndef AST_H_
#define MYCALC_AST_H_

#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/variant/static_visitor.hpp>

#include <string>
#include <memory>

#include "AstBase.h"
#include "../semantics/type.h"

namespace mycalc {
    namespace ast {
        class IntExpr;
        class FloatExpr;
        class BinOpExpr;

        using AnyExpr = boost::variant<IntExpr, FloatExpr, boost::recursive_wrapper<BinOpExpr>>;
    }
}

#endif // MYCALC_AST_H_