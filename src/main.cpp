#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_os_ostream.h>
#include <fstream>
#include <iterator>

#include "mycalc/lib.h"
#include "mycalc/ast/ast.h"
#include "mycalc/codegen.h"

bool loop(mycalc::codegen::LLVMCodeGenerator&, int);

int main(int argc, char **argv) {
    static llvm::LLVMContext ctx;
    mycalc::codegen::LLVMCodeGenerator gen{"Toplevel", ctx};

    auto cnt = 0;
    while (loop(gen, cnt++)) {

    }

    std::ofstream out{argv[1], std::ios_base::out};
    llvm::raw_os_ostream o{out};
    gen.getModule()->print(o, nullptr);
    return 0;
}

bool loop(mycalc::codegen::LLVMCodeGenerator &gen, int cnt) {
    std::string line;
    std::cout << "user> ";
    std::flush(std::cout);

    std::getline(std::cin, line);
    if (line == "quit") {
        return false;
    }

    auto ast = mycalc::parse(line);
    std::cout << mycalc::ast::visitor::stringize(ast) << std::endl;

    if (!gen.generate(ast, "func" + std::to_string(cnt++))) {
        std::cerr << "Error: failed code generation" << std::endl;
        return true;
    }

    if (llvm::verifyModule(*gen.getModule())) {
        std::cerr << "something goes wrong" << std::endl;
    }

    gen.getModule()->print(llvm::errs(), nullptr);
    return true;
}
