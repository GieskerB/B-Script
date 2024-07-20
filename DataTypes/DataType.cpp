#include "DataTypes.hpp"

namespace dat {

    DataType::DataType(const lex::Position &pos_start, const lex::Position &pos_end, itp::Context *context,
                       const DataTypeType &type) : m_position_start(pos_start), m_position_end(pos_end),
                                                   p_context(context), c_DATATYPE_TYPE(type) {}


    void DataType::set_position(const lex::Position &start, const lex::Position &end) {
        m_position_start = start;
        m_position_end = end;
    }

    void DataType::set_context(itp::Context &context) {
        p_context = &context;
    }

    void DataType::virtual_method() {

    }

//    std::pair<lex::Position, lex::Position> DataType::get_position() const {
//        return {m_position_start,m_position_end};
//    }
//
//    itp::Context DataType::get_context() const {
//        return *p_context;
//    }



}