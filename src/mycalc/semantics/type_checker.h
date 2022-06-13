#ifndef MYCALC_TYPE_CHECKER_H_
#define MYCALC_TYPE_CHECKER_H_

#include "type.h"
#include "../ast/ast.h"

#include <boost/variant/static_visitor.hpp>
#include <boost/optional.hpp>

namespace mycalc {
    namespace semantics {
        namespace type {
            class TypeInferer: public boost::static_visitor<PrimitiveType> {
            public:
                PrimitiveType operator()(ast::IntExpr &i);
                PrimitiveType operator()(ast::FloatExpr &f);
                PrimitiveType operator()(ast::BinOpExpr &);
            };

            PrimitiveType inferExpressionType(ast::AnyExpr &ast);
        }
    }
}

#endif // MYCALC_TYPE_CHECKER_H_