#ifndef MYCALC_AST_H_
#define MYCALC_AST_H_

#include <utility>
#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/variant/static_visitor.hpp>

#include <string>
#include <memory>

#include "ast_base.h"
#include "../semantics/type.h"

namespace mycalc {
    namespace ast {
        class IntExpr;
        class FloatExpr;
        class BinOpExpr;

        using AnyExpr = boost::variant<IntExpr, FloatExpr, boost::recursive_wrapper<BinOpExpr>>;

        class ExprBase: public AstBase {
            std::shared_ptr<semantics::type::AnyType> type;
        public:
            ExprBase(): type(std::make_shared<semantics::type::AnyType>(semantics::type::UnknownType{})) {}

            template<typename T>
            ExprBase(T const &&ty): type(std::make_shared<semantics::type::AnyType>(ty)) {}

            void setType(semantics::type::AnyType const &ty) {
                this->type = std::make_shared<semantics::type::AnyType>(ty);
            }

            semantics::type::AnyType const& getType() const {
                return *this->type;
            }
        };

        class IntExpr: public ExprBase {
            int val;
        public:
            IntExpr(): val(0) {}
            IntExpr(int v): ExprBase(semantics::type::PrimitiveType{semantics::type::PrimitiveType::Int}), val(v) {}

            int getVal() const {
                return val;
            }
        };

        class FloatExpr: public ExprBase {
            float val;
        public:
            FloatExpr(): val(0.0) {}
            FloatExpr(float v): ExprBase(semantics::type::PrimitiveType{semantics::type::PrimitiveType::Float}), val(v) {}

            float getVal() const {
                return val;
            }
        };

        class BinOpExpr: public ExprBase {
            std::string op;
            AnyExpr lhs;
            AnyExpr rhs;
        public:
            BinOpExpr(std::string op, AnyExpr &lhs, AnyExpr &rhs):
                    ExprBase(semantics::type::UnknownType{}),
                    op(std::move(op)),
                    lhs(lhs),
                    rhs(rhs) {}

            std::string const& getOp() const {
                return this->op;
            }

            AnyExpr const& getLhs() const {
                return this->lhs;
            }

            AnyExpr& getLhs() {
                return this->lhs;
            }

            AnyExpr const& getRhs() const {
                return this->rhs;
            }

            AnyExpr& getRhs() {
                return this->rhs;
            }
        };

        namespace visitor {
            class Stringizer: public boost::static_visitor<std::string> {
            public:
                std::string operator()(IntExpr const&) const;
                std::string operator()(FloatExpr const&) const;
                std::string operator()(BinOpExpr const&) const;
            };

            std::string stringize(ast::AnyExpr const);
        }
    }
}

#endif // MYCALC_AST_H_