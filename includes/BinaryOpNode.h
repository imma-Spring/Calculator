#pragma once
#include "ASTNode.h"
#include "TokenType.h"
#include <memory>
class BinaryOpNode :
    public ASTNode
{
public:
    BinaryOpNode(TokenType op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
        : m_op(op), m_left(std::move(left)), m_right(std::move(right)) {}

    TokenType getOperator() const
    {
        return m_op;
    }

    const ASTNode* getLeftOperand() const
    {
        return m_left.get();
    }

    const ASTNode* getRightOperand() const
    {
        return m_right.get();
    }

private:
    TokenType m_op;
    std::unique_ptr<ASTNode> m_left;
    std::unique_ptr<ASTNode> m_right;
};