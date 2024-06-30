#ifndef B_SHARP_POSITION_HPP
#define B_SHARP_POSITION_HPP


#include <string>

namespace lex {
    class Position {
    private:
        int m_index, m_line, m_column;
        std::string m_file_name;

    public:

        static const Position NULL_POSITION;

        Position() = delete;
        Position(int, int, int, std::string);
        Position(const Position&) =default;

        [[nodiscard]]  int index() const;

        [[nodiscard]]  int column() const;

        [[nodiscard]]  int line() const;

        [[nodiscard]]  std::string file_name() const;

         void advance(char = '\0');

        bool operator==(const Position&) const = default;

    };
} // lex

#endif //B_SHARP_POSITION_HPP
