#include <iostream>;
using namespace std;

struct CodeLocation
{
    int line;
    int col_number;
    string print() const;
};