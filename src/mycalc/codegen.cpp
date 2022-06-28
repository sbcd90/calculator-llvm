#include "codegen.h"
#include "semantics/type_checker.h"
#include <iostream>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_os_ostream.h>

namespace mycalc {
    namespace codegen {
        LLVMCodeGenerator::LLVMCodeGenerator(const std::string &modName, llvm::LLVMContext &ctx):
            ctx(ctx), module(modName, ctx), builder(ctx) {}

        bool LLVMCodeGenerator::generate(ast::AnyExpr &ast, const std::string &funcName) {
            semantics::type::PrimitiveType exprType = semantics::type::inferExpressionType(ast);
            llvm::FunctionType *ft;
            if (exprType == semantics::type::PrimitiveType::Int) {
                std::cout << "this is an integer expression" << std::endl;
                ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(ctx), llvm::ArrayRef<llvm::Type*>(), false);
            } else {
                std::cout << "this is an float expression" << std::endl;
                ft = llvm::FunctionType::get(llvm::Type::getFloatTy(ctx), llvm::ArrayRef<llvm::Type*>(), false);
            }

            if (!ft) {
                std::cerr << "null 1" << std::endl;
            }
            f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, funcName, &module);
            if (!f) {
                std::cerr << "null 2" << std::endl;
            }

            llvm::BasicBlock *bb = llvm::BasicBlock::Create(ctx, "entry", f);
            if (!bb) {
                std::cerr << "null 4" << std::endl;
            }
            builder.SetInsertPoint(bb);

            auto retVal = boost::apply_visitor(*this, ast);
            if (!retVal) {
                return false;
            }
            builder.CreateRet(retVal);

            llvm::raw_os_ostream s{std::cerr};
            if (llvm::verifyFunction(*f, &s)) {
                std::cerr << "something goes wrong in function" << std::endl;
                return false;
            }
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