#include <Lexer.h>
#include <assert.h>
#include <algorithm>
#include <cctype>

Lexer::Lexer(const std::filesystem::path &path)
    : reader(path), currentToken(TokenType::TOK_EOF)
{
    advance();
}

const Token &Lexer::getToken() const { return currentToken; }

void Lexer::advance()
{
    while(isspace(reader.getChar()) && !reader.isEOF())
    {
        reader.advance();
        
    }
    currentToken = consumeToken();
}

void Lexer::expect(TokenType expectedType) 
{
  assert(currentToken.type == expectedType);
  advance();
}

void Lexer::expectOneOf(const std::initializer_list<TokenType> &expectedTypes) 
{
  const auto matcher = [&](const TokenType &expectedType) { return currentToken.type == expectedType; };
  assert(std::any_of(expectedTypes.begin(), expectedTypes.end(), matcher));
  advance();
}
bool Lexer::isEOF() const { return reader.isEOF(); }

CodeLocation Lexer::getCodeLoc() const { return reader.getCodeLoc(); }


Token Lexer::consumeToken() {
  
  const char curChar = reader.getChar();


  if (reader.isEOF())
    return Token(TOK_EOF, "EOF", reader.getCodeLoc());

  if (isalpha(curChar) || curChar == '_')
    return consumeKeywordOrIdentifier();
  if (isdigit(curChar))
    return consumeNumber();

  reader.advance();
  switch (curChar) {
  case '=':
    return Token(TOK_ASSIGN, "=", reader.getCodeLoc());
  case '+':
    return Token(TOK_PLUS, "+", reader.getCodeLoc());
  case '-':
    return Token(TOK_MINUS, "-", reader.getCodeLoc());
  case '*':
    return Token(TOK_MUL, "*", reader.getCodeLoc());
  case '/':
    return Token(TOK_DIV, "/", reader.getCodeLoc());
  case ';':
    return Token(TOK_SEMICOLON, ";", reader.getCodeLoc());
  case '(':
    return Token(TOK_LPAREN, "(", reader.getCodeLoc());
  case ')':
    return Token(TOK_RPAREN, ")", reader.getCodeLoc());
  }

  assert(false && "Unexpected char");
}

Token Lexer::consumeNumber() {
  std::stringstream numberStream;

  
  const CodeLocation codeLoc = reader.getCodeLoc();
  bool seenDot = false;
  do {
    char c = reader.getChar();
    if (c == '.')
      seenDot = true;
    numberStream << c;
    reader.advance();
  } while (isdigit(reader.getChar()) || (reader.getChar() == '.' && !seenDot));

  return Token(seenDot ? TOK_DOUBLE_LIT : TOK_INT_LIT, numberStream.str(), codeLoc);
}

Token Lexer::consumeKeywordOrIdentifier() {
  std::stringstream identStream;

  // Read identifier using regex [a-zA-Z0-9_]*
  const CodeLocation codeLoc = reader.getCodeLoc();
  do {
    identStream << reader.getChar();
    reader.advance();
  } while (isalnum(reader.getChar()) || reader.getChar() == '_');

  
  const std::string &ident = identStream.str();
  if (ident == "int")
    return Token(TOK_TYPE_INT, "int", codeLoc);
  if (ident == "double")
    return Token(TOK_TYPE_DOUBLE, "double", codeLoc);
  if (ident == "print")
    return Token(TOK_PRINT, "print", codeLoc);

  return Token(TOK_IDENTIFIER, ident, codeLoc);
}

Token Lexer::consumeSemicolon() {
  reader.expect(TOK_SEMICOLON);
  return Token(TOK_SEMICOLON, ";", reader.getCodeLoc());
}