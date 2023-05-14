#include "includes/Interpreter.h"
#include <stdexcept>
#include <cmath>

double Interpreter::interpret(const ASTNode* root) {
        if (root == nullptr) {
            return 0.0;
        }

        if (const NumberNode* numNode = dynamic_cast<const NumberNode*>(root)) {
            return numNode->getValue();
        }

        if (const BinaryOpNode* opNode = dynamic_cast<const BinaryOpNode*>(root)) {
            double leftValue = interpret(opNode->getLeftOperand());
            double rightValue = interpret(opNode->getRightOperand());
            TokenType op = opNode->getOperator();

            switch (op) {
            case TokenType::PLUS:
                return leftValue + rightValue;
            case TokenType::MINUS:
                return leftValue - rightValue;
            case TokenType::MULTIPLY:
                return leftValue * rightValue;
            case TokenType::DIVIDE:
                if (rightValue != 0.0) {
                    return leftValue / rightValue;
                }
                else {
                    throw std::runtime_error("Division by zero!");
                }
            case TokenType::POWER:
                return std::pow(leftValue, rightValue);
            default:
                throw std::runtime_error("Unknown operator!");
            }
        }

        throw std::runtime_error("Invalid AST node!");
    }
