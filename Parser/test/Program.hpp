//
// Created by bjarn on 18.10.2024.
//

#ifndef B_SHARP_PROGRAM_HPP
#define B_SHARP_PROGRAM_HPP

#include "Statement.hpp"
#include "../../Interpreter/Context.hpp"
#include <vector>
#include <memory>

typedef std::vector<std::shared_ptr<Statement>> ProgramBody;

class Program :  public Statement {

private:
    ProgramBody m_body;
    itp::Context m_context{"Global Context"};

public:

    Program();
    ~Program() override = default;

    [[nodiscard]] const ProgramBody& statements() const;
    [[nodiscard]] const itp::Context& context() const;
    void add_statement(const std::shared_ptr<Statement>&);
};


#endif //B_SHARP_PROGRAM_HPP
