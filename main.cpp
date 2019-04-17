#include "Lexer.h"

std::ostream& operator <<(std::ostream& out, const Token& t)
{
	switch (int(t))
	{
		case 0:
			out << "int_const";
			break;
		case 1:
			out << "float_const";
			break;
		case 2:
			out << "add";
			break;
		case 3:
			out << "sub";
			break;
		case 4:
			out << "multi";
			break;
		case 5:
			out << "divi";
			break;
		case 6:
			out << "open_parens";
			break;
		case 7:
			out << "close_parens";
			break;
		case 8:
			out << "greater_than";
			break;
		case 9:
			out << "greater_equal";
			break;
		case 10:
			out << "lesser_than";
			break;
		case 11:
			out << "lesser_equal";
			break;
		case 12:
			out << "is_equal";
			break;
		case 13:
			out << "different";
			break;
		default:
			out << "Type not found (mismatch)";
	}
	return out;
}

int main() {
    Lexer lex = Lexer();

    //std::cout << lex.isDigit('.') << lex.isDigit('\\') << lex.isDigit('c') << lex.isDigit('9');
    cout << lex.getToken();
    return 0;
}