#include <CodeLoc.h>

string CodeLocation::print() const
{
    return "(" + to_string(line) + "," + to_string(col_number) + ")";
}
