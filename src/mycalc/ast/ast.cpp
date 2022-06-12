#include "ast.h"
#include <boost/variant/variant.hpp>
#include <string>

namespace mycalc {
    namespace ast {
        namespace visitor {
            std::string Stringizer::operator()(const IntExpr &i) const {
                return std::to_string(i.getVal());
            }

            std::string Stringizer::operator()(const FloatExpr &f) const {
                return std::to_string(f.getVal());
            }

            std::string Stringizer::operator()(const BinOpExpr &bin) const {
                return "(" + boost::apply_visitor(Stringizer{}, bin.getLhs()) + " " +
                bin.getOp() + " " + boost::apply_visitor(Stringizer{}, bin.getRhs()) + ")";
            }

            std::string stringize(const ast::AnyExpr ast) {
                Stringizer s{};
                return boost::apply_visitor(s, ast);
            }
        }
    }
}