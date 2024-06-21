//
// Created by bjarn on 18.06.2024.
//

#include "Error.hpp"

#include <utility>
#include <iostream>

namespace err {
    Error::Error(std::string name, std::string message): m_name(std::move(name)), m_message(std::move(message)) {}

    void Error::print() {
        std::cerr << m_name << ": " << m_message << '\n';
    }

    IllegalCharError::IllegalCharError(std::string message): Error("IllegalCharError", std::move(message)) {

    }
} // err