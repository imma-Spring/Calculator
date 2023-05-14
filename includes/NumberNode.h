#pragma once
#include "ASTNode.h"
class NumberNode :
    public ASTNode
{
public:
    explicit NumberNode(double value) : m_value(value) {}

    double getValue() const
    {
        return m_value;
    }

private:
    double m_value;
};

