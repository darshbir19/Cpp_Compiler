#include <Token.h>
#include "../reader/Reader.h"
using namespace std;

class Lexer  
{
    public:
        explicit Lexer(const filesystem::path& path);

        const Token &getToken() const;
        void advance();
        void expect(TokenType expectedType);
        void expectOneOf(const initializer_list<TokenType> &expectedTypes);
        bool isEOF() const;
        CodeLocation getCodeLoc() const;

    private:
    Reader reader;
    Token currentToken;
    Token consumeToken();
    Token consumeNumber();
    Token consumeKeywordOrIdentifier();
    Token consumeSemicolon();
};