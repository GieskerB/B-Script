#ifndef B_SHARP_UTILITY_HPP
#define B_SHARP_UTILITY_HPP

#include <variant>
#include <string>

#include "Boolean.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "String.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    DataType &get_variant_content(VariantTypes &variant);

    std::string number_to_string(uint64, bool);
    uint64 string_to_number(const std::string &);
    VariantTypes create_datatype_form_string(const std::string &);
    std::pair<uint128, bool>storage_addition(uint128 , uint128 , bool , bool );
    std::pair<uint64, bool>storage_addition(uint64 , uint64 , bool , bool );
    std::tuple<bool,bool,bool>storage_comparison(uint128 , uint128 , bool , bool );
    std::tuple<bool,bool,bool>storage_comparison(uint64 , uint64 , bool , bool );
    std::pair<uint128, uint128>shift_to_equal_size( uint64 ,  uint64 ,  char );
    uint64 unshift_form_equal_size( uint128 ,  char ) ;
    std::pair<lex::Position, lex::Position> get_position_form_variant(const VariantTypes &);

    std::ostream & operator<<(std::ostream &, const VariantTypes&);

    VariantTypes operator+(const VariantTypes&, const VariantTypes&);
    VariantTypes operator-(const VariantTypes&, const VariantTypes&);
    VariantTypes operator*(const VariantTypes&, const VariantTypes&);
    VariantTypes operator/(const VariantTypes&, const VariantTypes&);

    VariantTypes operator+(const VariantTypes&);
    VariantTypes operator-(const VariantTypes&);
    VariantTypes operator!(const VariantTypes&);

    Boolean operator<(const VariantTypes&, const VariantTypes&);
    Boolean operator>(const VariantTypes&, const VariantTypes&);
    Boolean operator<=(const VariantTypes&, const VariantTypes&);
    Boolean operator>=(const VariantTypes&, const VariantTypes&);
    Boolean operator==(const VariantTypes&, const VariantTypes&);
    Boolean operator!=(const VariantTypes&, const VariantTypes&);
    Boolean operator&&(const VariantTypes&, const VariantTypes&);
    Boolean operator||(const VariantTypes&, const VariantTypes&);


} // dat

#endif //B_SHARP_UTILITY_HPP
