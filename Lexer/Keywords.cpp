#include "Keywords.hpp"
#include "../DataTypes/Number.hpp"
#include "../DataTypes/Boolean.hpp"

namespace lex {

    Keywords::Keywords() {
        gen_var_types();
    }

    /*
     * Key structure:
     * XXXXXXXX:XXXXXXXX
     * EXTRAINF SSSSTTTT
     */
    void Keywords::gen_var_types() {
        int index = 0;
        var_type_names[index] = "bool";
        var_type_keys[var_type_names[index++]] = BITMAP_BOOL;
        var_type_names[index] = "str";
        var_type_keys[var_type_names[index++]] = BITMAP_STR;
        for (const auto &size: dat::sizes) {
            var_type_names[index] = "int" + std::to_string(size * 8);
            var_type_keys[var_type_names[index++]] = static_cast<short>(BITMAP_INT | (size << 4));
            var_type_names[index] = "uint" + std::to_string(size * 8);
            var_type_keys[var_type_names[index++]] = static_cast<short>(BITMAP_INT | (size << 4) | BITMAP_UNSIGNED);
            var_type_names[index] = "dec" + std::to_string(size * 8);
            var_type_keys[var_type_names[index++]] = static_cast<short>(BITMAP_DEC | (size << 4) |
                                                                        ((size * 8 / 2) << 8));
            if (size == 4) {
                var_type_names[index] = "int";
                var_type_keys[var_type_names[index++]] = static_cast<short>(BITMAP_INT | (size << 4));
                var_type_names[index] = "uint";
                var_type_keys[var_type_names[index++]] = static_cast<short>(BITMAP_INT | (size << 4) | BITMAP_UNSIGNED);
                var_type_names[index] = "dec";
                var_type_keys[var_type_names[index++]] = static_cast<short>(BITMAP_DEC | (size << 4) |
                                                                            ((size * 8 / 2) << 8));
            }
            for (char scale_fac = 0; scale_fac <= size * 8; ++scale_fac) {
                var_type_names[index] = "dec" + std::to_string(size * 8) + ':' + std::to_string(scale_fac);
                var_type_keys[var_type_names[index++]] = static_cast<short>(BITMAP_DEC | (size << 4) |
                                                                            (scale_fac << 8));
            }
        }
    }

    void Keywords::gen_constants() {
        constants[0] = dat::Boolean::TRUE;
        constants[1] = dat::Boolean::FALSE;
        constants[2] = dat::Boolean::NEUTRAL;
    }

    const Keywords &Keywords::get_instance() {
        static Keywords instance{};
        return instance;
    }

} // lex