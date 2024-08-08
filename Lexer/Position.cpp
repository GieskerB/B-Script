#include "Position.hpp"

#include <utility>

namespace lex {
    const Position Position::NULL_POSITION(-1, -1, -1,-1, "NULL");

    Position::Position(int index, int line, int column,int indentation, std::string file_name) : m_index(index), m_line(line),
                                                                                 m_column(column), m_indentation(indentation),
                                                                                 m_file_name(std::move(file_name)) {}

    int Position::index() const {
        return m_index;
    }

    int Position::line() const {
        return m_line;
    }

    int Position::column() const {
        return m_column;
    }

    int Position::indentation() const {
        return m_indentation;
    }

    std::string Position::file_name() const {
        return m_file_name;
    }

    void Position::enter_scope() {
        ++m_indentation;
    }

    void Position::leave_scope() {
        --m_indentation;
    }

    void Position::advance(char current_char) {
        ++m_index;
        if (current_char == '\n') {
            ++m_line;
            m_column = 0;
        } else {
            ++m_column;
        }
    }
} // lex