#include "Program.hpp"

Program::Program(): Statement(NodeType::PROGRAM) {}

const ProgramBody &Program::statements() const {
    return m_body;
}

const itp::Context &Program::context() const{
    return m_context;
}

void Program::add_statement(const std::shared_ptr<Statement> &statement) {
    m_body.push_back(statement);
}

