#ifndef MYCALC_TYPE_H_
#define MYCALC_TYPE_H_

#include <boost/variant/variant.hpp>
#include <memory>

namespace mycalc {
    namespace semantics {
        namespace type {
            enum class PrimitiveType {
                Int,
                Float
            };

            class UnknownType;

            using AnyType = boost::variant<PrimitiveType, UnknownType>;

            class UnknownType {
                std::shared_ptr<AnyType> innerVal;
            public:
                UnknownType(): innerVal(nullptr) {}
                UnknownType(AnyType const& ty): innerVal(std::make_shared<AnyType>(ty)) {}
            };
        }
    }
}

#endif // MYCALC_TYPE_H_