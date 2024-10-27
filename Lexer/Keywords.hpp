#ifndef B_SHARP_KEYWORDS_HPP
#define B_SHARP_KEYWORDS_HPP

#include <array>
#include <string>
#include <unordered_map>

namespace lex {

    class Keywords {
    private:
        static const short BITMAP_BOOL = 0b0001, BITMAP_STR = 0b0010, BITMAP_INT = 0b0100, BITMAP_DEC = 0b1000;
        static const short BITMAP_UNSIGNED = 0b0000000100000000;

        void gen_var_types();
        void gen_constants();

        Keywords();

    public:

        std::array<std::string, 141> var_type_names;
        std::unordered_map<std::string, short> var_type_keys;
        std::array<std::string,3> constants;

        static const Keywords &get_instance();
    };

    static const Keywords& keywords = Keywords::get_instance();

} // lex

#endif //B_SHARP_KEYWORDS_HPP
