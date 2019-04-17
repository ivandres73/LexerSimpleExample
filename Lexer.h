#include <iostream>
#include <string.h>

enum class Token {
    int_const,
    float_const,
    add,
    sub,
    multi,
    divi,
    open_parens,
    close_parens,
    greater_than,
    greater_equal,
    lesser_than,
    lesser_equal,
    is_equal,
    different
};

using std::cout;
using std::endl;

class Lexer {
    public:
        Lexer();
        Token getToken();
        std::string x;
        int i;
        
    private:
        int curr_st;

        char nextChar();
        void resetCurrentState();
        bool isDigit(char c);
        Token returnToken(Token t);
        void previousChar();

};