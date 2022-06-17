#include "parser.h"
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

namespace mycalc {
    namespace parser {
        namespace helper {
            template<typename Iter>
            inline auto line_pos_iterator(Iter i) {
                return boost::spirit::line_pos_iterator<Iter>(i);
            }

            template<class T, class Iter>
            void setPositionImpl(T &node, const Iter before, const Iter after, const Iter src) {
                auto d = std::distance(before.base(), after.base());
                node.line = boost::spirit::get_line(before);
                node.col = boost::spirit::get_column(src, before);
                node.length = d < 0? 0: d;
            }

            template<class Iter>
            struct SetPosition: public boost::static_visitor<> {
                const Iter before;
                const Iter after;
                const Iter src;

                SetPosition(const Iter before, const Iter after, const Iter src):
                    before(before), after(after), src(src) {}

                template<class T>
                void operator()(T &node) const {
                    setPositionImpl(node, before, after, src);
                }
            };

            template<typename Iter>
            struct Annotation_f {
                typedef void resultType;

                Annotation_f(const Iter src): src(src) {}

                template<typename Val, typename First, typename Last>
                void operator()(Val &v, First f, Last l) const {
                    doAnnotate(v, f, l);
                }

            private:
                const Iter src;

                void doAnnotate(ast::AnyExpr &ast, Iter f, Iter l) const {
                    SetPosition<Iter> s{f, l, src};
                    boost::apply_visitor(s, ast);
                }

                template<typename T>
                void doAnnotate(std::shared_ptr<T> &ast, Iter f, Iter l) const {
                    doAnnotate(*ast);
                }

                template<typename T>
                void doAnnotate(T &ast, Iter f, Iter l) const {
                    setPositionImpl(ast, f, l, src);
                }
            };
        }

        namespace qi = boost::spirit::qi;
        namespace phx = boost::phoenix;
        namespace ascii = boost::spirit::ascii;

        using namespace qi::labels;

        template<class Iter>
        class MyCalcGrammar: public qi::grammar<Iter, ast::AnyExpr, ascii::space_type> {
            template<class T>
            using rule = qi::rule<Iter, T, ascii::space_type>;

            phx::function<helper::Annotation_f<Iter>> annotate;
            rule<ast::IntExpr> intExpr;
            rule<ast::FloatExpr> floatExpr;
            rule<ast::AnyExpr> primaryExpr;
            rule<ast::AnyExpr> mulExpr;
            rule<ast::AnyExpr> addExpr;
            rule<ast::AnyExpr> expression;

            template<typename T>
            struct MakeSharedPtrLazy {
                typedef std::shared_ptr<T> ResultType;

                template<typename... Args>
                auto operator()(Args &&... args) const -> ResultType {
                    return std::make_shared<T>(std::forward<Args>(args)...);
                }
            };

            template<typename T, typename... Args>
            auto makeSharedPtr(Args &&... args) {
                return phx::function<MakeSharedPtrLazy<T>>()(std::forward<Args>(args)...);
            }

        public:
            MyCalcGrammar(const Iter src) {

            }
        };

        ast::AnyExpr MyCalcParser::parse(const std::string &src) const {
            auto begin = helper::line_pos_iterator(std::begin(src));
            using iterator_t = decltype(begin);
            auto end = helper::line_pos_iterator(std::end(src));

            std::cout << "hit" << std::endl;
            return {};
        }
    }
}