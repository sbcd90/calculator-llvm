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
        }

        namespace qi = boost::spirit::qi;
        namespace phx = boost::phoenix;
        namespace ascii = boost::spirit::ascii;

        using namespace qi::labels;

        template<class Iter>
        class MyCalcGrammar: public qi::grammar<Iter, ast::AnyExpr, ascii::space_type> {
            
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