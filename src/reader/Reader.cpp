#include <Reader.h>
#include <assert.h>

Reader::Reader(const filesystem::path &fPath)
{
    inputFile.open(fPath);
    if (!inputFile.is_open())
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    int ch = inputFile.get();
    if (ch == EOF)
    {
        curChar = '\0';
        moreToRead = false;
    }
    else 
    {
        curChar = static_cast<char>(ch);
        moreToRead = true;
    }
    curCodeLocation.line = 1;
    curCodeLocation.col_number = 0;
}

Reader::~Reader() {
  inputFile.close();
}

char Reader::getChar() const
{
    return curChar;
}

CodeLocation Reader::getCodeLoc() const
{
    return curCodeLocation;
}

void Reader::advance()
{
    assert(!isEOF());
    if (!inputFile.get(curChar))
    moreToRead = false;

    if (curChar == '\n')
    {
        curCodeLocation.line++;
        curCodeLocation.col_number = 0;
    }

    curCodeLocation.col_number++;
}

void Reader::expect(char c)
{
    advance();
    assert(curChar == c);
}