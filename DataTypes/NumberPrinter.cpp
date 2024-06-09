//
// Created by bjarn on 08.06.2024.
//

#include "NumberPrinter.hpp"
#include <iostream>

namespace num {

    struct Stack {
        char digit{0};
        Stack* previous{nullptr};
//        Stack(char d, Stack* p) {
//            digit = d;
//            previous = p;
//            std::cout << "alive";
//        }
//        ~Stack() {
//            std::cout << "dead";
//        }
    };

    void NumberPrinter::print_int(const num::Integer &number) {
//        std::cout << number.m_storage << " " <<number.m_is_positive <<std::endl;
        uint64 storage = number.m_storage;
        Stack* number_stack{};

        while (storage != 0) {
            unsigned char digit = storage % 10;
            storage /= 10;
            auto* next_element = new Stack(static_cast<char>(digit + '0'), number_stack);
            number_stack = next_element;
        }
        if(!number.m_is_positive) {
            auto* next_element = new Stack(static_cast<char>('-'), number_stack);
            number_stack = next_element;
        }

        while(number_stack != nullptr and number_stack->digit != 0) {
            std::cout << number_stack->digit ;
            Stack* temp = number_stack;
            number_stack = number_stack->previous;
            delete temp;
        }
        std::cout  <<std::endl;
        delete number_stack;
    }

    void NumberPrinter::print_dec(const num::Integer &number) {

    }

} // num