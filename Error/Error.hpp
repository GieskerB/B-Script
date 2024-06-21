//
// Created by bjarn on 18.06.2024.
//

#ifndef B_SHARP_ERROR_HPP
#define B_SHARP_ERROR_HPP

#include <string>

namespace err {

    class Error : std::exception {

        std::string m_name,m_message;

    protected:

        Error(std::string ,std::string);

    public:

        Error() = delete;

        void print();

    };

    class IllegalCharError : public Error {
    public:
        IllegalCharError() = delete;
        explicit IllegalCharError(std::string);

    };

} // err

#endif //B_SHARP_ERROR_HPP
