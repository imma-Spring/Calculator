#pragma once
#include "BinaryOpNode.h"
#include "NumberNode.h"
class Interpreter {
public:
    double interpret(const ASTNode* root);
};


