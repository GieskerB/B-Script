#ifndef B_SHARP_POSITION_HPP
#define B_SHARP_POSITION_HPP

#include <string>

namespace lex {
    class Position {

        int m_index, m_line, m_column, m_indentation;
        std::string m_file_name;


    public:

        static const Position NULL_POSITION;

        Position() = delete;
        Position(int, int, int,int, std::string);
        Position(const Position&) =default;

        [[nodiscard]]  int index() const;
        [[nodiscard]]  int line() const;
        [[nodiscard]]  int column() const;
        [[nodiscard]]  int indentation() const;

        void enter_scope();
        void leave_scope();

        [[nodiscard]]  std::string file_name() const;

         void advance(char = '\0');

        bool operator==(const Position&) const = default;

    };
} // lex

#endif //B_SHARP_POSITION_HPP
