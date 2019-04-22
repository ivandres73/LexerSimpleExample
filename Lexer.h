#include <iostream>
#include <fstream>
#include <string.h>
//#include <stdexcept>

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
using std::string;

class Lexer {
    public:
        Lexer();
        Token getToken();
        bool isEOF();
        void closeFile();
        void openFile();
        string getCurrentLexeme();
        int getLine();
        
    private:
        int curr_st;
        int line;
        int file_pos;
        fstream file;
        char c;//current char of the file
        string lexeme;

        void nextChar();
        void resetCurrentState();
        bool isDigit(char c);
        Token returnToken(Token t);
        void previousChar();
        void emptyLexeme();
};