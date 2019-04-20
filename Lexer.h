#include <iostream>
#include <fstream>

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
    different,
    end_file
};

using std::cout;
using std::endl;
using std::fstream;

class Lexer {
    public:
        Lexer();
        Token getToken();
        fstream file;
        
    private:
        int curr_st;
        int line;
        int file_pos;
        char c;//current char of the file

        void nextChar();
        void resetCurrentState();
        bool isDigit(char c);
        Token returnToken(Token t);
        void previousChar();

};