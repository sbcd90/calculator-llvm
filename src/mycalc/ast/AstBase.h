#ifndef MYCALC_AST_BASE_H_
#define MYCALC_AST_BASE_H_

namespace mycalc {
    namespace ast {
        class AstBase {
        public:
            int line;
            int col;
            int length;
        };
    }
}

#endif // MYCALC_AST_BASE_H_