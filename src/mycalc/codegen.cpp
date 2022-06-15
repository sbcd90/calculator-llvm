#include "codegen.h"

namespace mycalc {
    namespace codegen {
        LLVMCodeGenerator::LLVMCodeGenerator(const std::string &modName, llvm::LLVMContext &ctx):
            ctx(ctx), module(modName, ctx), builder(ctx) {}

        bool LLVMCodeGenerator::generate(ast::AnyExpr &ast, const std::string &funcName) {
            return true;
        }

        llvm::Value* LLVMCodeGenerator::operator()(const ast::IntExpr &i) {
            return {};
        }

        llvm::Value* LLVMCodeGenerator::operator()(const ast::FloatExpr &x) {
            return {};
        }

        llvm::Value* LLVMCodeGenerator::operator()(const ast::BinOpExpr &binOp) {
            return {};
        }
    }
}