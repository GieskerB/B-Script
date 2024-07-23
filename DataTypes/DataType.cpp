#include "DataType.hpp"

namespace dat {

    DataType::DataType(const lex::Position &start_pos, const lex::Position &end_pos, itp::Context *context)
            : m_position_start(start_pos),
              m_position_end(end_pos), p_context(context) {}

    void DataType::set_position(const lex::Position &start_pos, const lex::Position &end_pos) {
        m_position_start = start_pos;
        m_position_end = end_pos;
    }

    void DataType::set_context(itp::Context & context) {
        p_context = & context;
    }




} // dat