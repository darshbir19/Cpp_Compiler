#include <string>
using namespace std;
#include "../reader/Reader.h"


enum TokenType {
  TOK_INVALID,
  TOK_INT_LIT,
  TOK_DOUBLE_LIT,
  TOK_IDENTIFIER,
  TOK_TYPE_INT,
  TOK_TYPE_DOUBLE,
  TOK_PRINT,
  TOK_ASSIGN,
  TOK_PLUS,
  TOK_MINUS,
  TOK_MUL,
  TOK_DIV,
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_SEMICOLON,
  TOK_EOF
};

struct Token
{
    TokenType type;
    string text;
    CodeLocation codeLoc;
    explicit Token(TokenType type) : type(type) {}
    Token(TokenType type, const std::string &text, const CodeLocation &codeLoc) : type(type), text(text), codeLoc(codeLoc) {}
    Token(const Token &) = delete;
};
