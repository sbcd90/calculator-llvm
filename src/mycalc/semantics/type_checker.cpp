#include "type_checker.h"

namespace mycalc {
    namespace semantics {
        namespace type {
            PrimitiveType TypeInferer::operator()(ast::IntExpr &i) {
                return PrimitiveType::Int;
            }

            PrimitiveType TypeInferer::operator()(ast::FloatExpr &f) {
                return PrimitiveType::Float;
            }

            PrimitiveType TypeInferer::operator()(ast::BinOpExpr &ast) {
                auto lType = boost::apply_visitor(*this, ast.getLhs());
                auto rType = boost::apply_visitor(*this, ast.getRhs());
                if (PrimitiveType::Float == lType || PrimitiveType::Float == rType) {
                    ast.setType(PrimitiveType::Float);
                    return PrimitiveType::Float;
                }
                ast.setType(PrimitiveType::Int);
                return PrimitiveType::Int;
            }

            PrimitiveType inferExpressionType(ast::AnyExpr &ast) {
                TypeInferer i{};
                return boost::apply_visitor(i, ast);
            }
        }
    }
}