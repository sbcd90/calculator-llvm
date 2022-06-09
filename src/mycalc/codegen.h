#ifndef MYCALC_CODEGEN_H_
#define MYCALC_CODEGEN_H_

#include "ast/Ast.h"
#include <boost/variant/static_visitor.hpp>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include <string>

namespace mycalc {
    namespace codegen {
        class LLVMCodeGenerator: public boost::static_visitor<llvm::Value*> {
            llvm::LLVMContext &ctx;
            llvm::Module module;
            llvm::IRBuilder<> builder;
            llvm::Function *f;
        public:
            LLVMCodeGenerator(std::string const&, llvm::LLVMContext&);
            bool generate(ast::AnyExpr&, std::string const&);

            llvm::Module* getModule() {
                return &module;
            }

            llvm::IRBuilder<>& getBuilder() {
                return builder;
            }

            llvm::Value* operator()(ast::IntExpr const&);
            llvm::Value* operator()(ast::FloatExpr const&);
            llvm::Value* operator()(ast::BinOpExpr const&);
        };
    }
}

#endif // MYCALC_CODEGEN_H_