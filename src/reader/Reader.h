#include <CodeLoc.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;
using namespace std::filesystem;

//Responsible for opening file and  reading it.

class Reader
{
    public:
        explicit Reader(filesystem::path &fPath);
        ~Reader();

        char getChar() const;
        CodeLocation getCodeLoc() const;
        void advance();
        void expect(char);
        bool isEOF() const;

    private:
        ifstream inputFile;
        char curChar = '\0';
        bool moreToRead = true;
        CodeLocation curCodeLocation{1ull, 0ull};

};