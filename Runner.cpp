#include "includes/Lexer.h"
#include "includes/Parser.h"
#include "includes/Interpreter.h"
#include <vector>

std::ostream& operator<< (std::ostream& os, TokenType tokentype)
{
    switch (tokentype)
    {
    case TokenType::NUMBER:
        os << "Number";
        break;
    case TokenType::PLUS:
        os << "+";
        break;
    case TokenType::MINUS:
        os << "-";
        break;
    case TokenType::MULTIPLY:
        os << "*";
        break;
    case TokenType::DIVIDE:
        os << "/";
        break;
    case TokenType::POWER:
        os << "**";
        break;
    case TokenType::LPAREN:
        os << "LParen ";
        break;
    case TokenType::RPAREN:
        os << "RParen ";
        break;
    case TokenType::INVALID:
        os << "Invalid ";
        break;
    }
    return os;
}

void printAST(const ASTNode* node, int level = 0, bool isRightChild = false) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < level; ++i) {
        std::cout << "     ";
    }

    if (const NumberNode* numNode = dynamic_cast<const NumberNode*>(node)) {
        std::cout << (isRightChild ? "|--- " : "|--- ") << numNode->getValue() << std::endl;
    }
    else if (const BinaryOpNode* opNode = dynamic_cast<const BinaryOpNode*>(node)) {
        std::cout << (isRightChild ? "|--- " : "|--- ") << opNode->getOperator() << std::endl;

        printAST(opNode->getLeftOperand(), level + 1, false);
        printAST(opNode->getRightOperand(), level + 1, true);
    }
}



int main()
{
    std::string input;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, input);

    Lexer lexer(input);
    Token token;

    std::vector<Token> tokens;
    while ((token = lexer.getNextToken()).type != TokenType::EOI && token.type != TokenType::INVALID)
    {
        tokens.push_back(token);
    }

    // Parse the expression and build the AST
    Parser parser(tokens);
    std::unique_ptr<ASTNode> ast = parser.parseExpression();


    // Print the tokens
    for (const Token& token : tokens) {
        std::cout << token << std::endl;
    }

    printAST(ast.get());
    Interpreter interpreter;
    double result = interpreter.interpret(ast.get());
    std::cout << "Result: " << result << std::endl;

    return 0;
}


