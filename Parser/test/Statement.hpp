#ifndef B_SHARP_STATEMENT_HPP
#define B_SHARP_STATEMENT_HPP

#include "NodeType.hpp"

class Statement {

protected:
    const NodeType c_type;

public:
    Statement() = delete;
    virtual ~Statement() = default;
    explicit Statement(const NodeType &);
    [[nodiscard]] NodeType get_type() const;
};


#endif //B_SHARP_STATEMENT_HPP
