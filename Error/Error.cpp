//
// Created by bjarn on 18.06.2024.
//

#include "Error.hpp"
#include "../FileReader/FileReader.hpp"

#include <fstream>
#include <limits>
#include <utility>
#include <iostream>

namespace err {

    void Error::underline_with_arrows() const {
        FileReader fr;
        fr.open_file(m_start_pos.file_name());
        std::string line = fr.read_line(m_start_pos.line());

        int error_column_start = m_start_pos.column();
        int error_column_end =
                m_start_pos.column() == m_end_pos.column() ? m_end_pos.column(): static_cast<int>(line.size() - 1);

        std::string result;
        std::cerr << '\n' << line << '\n';
        result.insert(0, error_column_start, ' ');
        result.insert(error_column_start, error_column_end - error_column_start+1, '^');
        std::cerr << result << '\n';

    }

    Error::Error(std::string name, lex::Position  start, lex::Position  end, std::string message) : m_name(
            std::move(name)), m_message(std::move(message)), m_start_pos(std::move(start)), m_end_pos(std::move(end)) {}

    void Error::print() {
        std::cerr << m_name << ": " << m_message << '\n'
                  << "File " << m_start_pos.file_name() << ", line " << m_start_pos.line() << '\n';
        underline_with_arrows();
    }

    IllegalCharError::IllegalCharError(const lex::Position& pos, std::string message) : Error(
            "IllegalCharError", pos,pos, std::move(message)) {}

    InvalidSyntaxError::InvalidSyntaxError(const lex::Position& start, const lex::Position& end, std::string message) : Error(
            "IllegalCharError", start,end, std::move(message)) {}


} // err