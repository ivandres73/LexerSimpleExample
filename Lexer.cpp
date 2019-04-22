#include "Lexer.h"

Lexer::Lexer()
{
    curr_st = 0;
    line = 1;
    lexeme = "";
}

void Lexer::nextChar()
{
    c = file.get();
}

Token Lexer::getToken()
{
	resetCurrentState();
	emptyLexeme();
	while (true)
	{
		nextChar();
		/*cout << " -> q" << curr_st;
		cout << "[" << c << "]";*/

    	switch(curr_st)
    	{
			case 0:
				if (file.eof())
					return returnToken(Token::end_file);
				if (c == '\n') {
					line++;
					continue;	
				}
				else if (c == '\t' || c == ' ')
					continue;
				else if (isDigit(c))
					curr_st = 1;
				else if (c == '+')
					curr_st = 5;
				else if (c == '-')
					curr_st = 6;
				else if (c == '*')
					curr_st = 7;
				else if (c == '>')
					curr_st = 9;
				else if (c == '<')
					curr_st = 12;
				else if (c == '(')
					curr_st = 15;
				else if (c == ')')
					curr_st = 16;
				else if (c == '=')
					curr_st = 17;
				else if (c == '!')
					curr_st = 19;
				else if (c == '/')
					curr_st = 21;
				else
					throw "invalid symbol";
				break;
			case 1:
				if (isDigit(c))
					curr_st = 1;
				else if (c == '.')
					curr_st = 3;
				else if (file.eof())
					return returnToken(Token::int_const);
				else
					return returnToken(Token::int_const);
				break;
			/*case 2:
				return returnToken(Token::int_const);*/
			case 3:
				if (isDigit(c))
					curr_st = 3;
				else if (file.eof())
					return returnToken(Token::float_const);
				else
					return returnToken(Token::float_const);
				break;
			/*case 4:
				return returnToken(Token::float_const);*/
			case 5:
				return returnToken(Token::add);
			case 6:
				return returnToken(Token::sub);
			case 7:
				return returnToken(Token::multi);
			/*case 8:
				return returnToken(Token::divi);*/
			case 9:
				if (c == '=')
					curr_st = 11;
				else if (file.eof())
					return returnToken(Token::greater_than);
				else
					return returnToken(Token::greater_than);
				break;
			/*case 10:
				return returnToken(Token::greater_than);*/
			case 11:
				return returnToken(Token::greater_equal);
			case 12:
				if (c == '=')
					curr_st = 14;
				else if (file.eof())
					return returnToken(Token::lesser_equal);
				else
					return returnToken(Token::lesser_equal);
				break;
			/*case 13:
				return returnToken(Token::lesser_than);*/
			case 14:
				return returnToken(Token::lesser_equal);
			case 15:
				return returnToken(Token::open_parens);
			case 16:
				return returnToken(Token::close_parens);
			case 17:
				if (c == '=')
					curr_st = 18;
				else
					throw "invalid symbol";
				break;
			case 18:
				return returnToken(Token::is_equal);
			case 19:
				if (c == '=')
					curr_st = 20;
				else
					throw "invalid symbol";
				break;
			case 20:
				return returnToken(Token::different);
			case 21:
				if (c == '/') {
					curr_st = 22;
					continue;
				} else if (c == '*') {
					curr_st = 23;
					continue;
				} else if (file.eof())
					return returnToken(Token::divi);
				else
					return returnToken(Token::divi);
				break;
			case 22:
				if (c == '\n') {
					curr_st = 0;
					continue;
				} else if (file.eof())
					return returnToken(Token::end_file);
				else
					continue;
				break;
			case 23:
				if (c == '*') {
					curr_st = 24;
					continue;
				} else if (file.eof())
					return returnToken(Token::end_file);
				else
					continue;
			case 24:
				if (c == '*')
					continue;
				else if (c == '/') {
					curr_st = 0;
					continue;
				} else if (file.eof())
					return returnToken(Token::end_file);
				else
					curr_st = 23;
				break;
    	}
    	lexeme += c;
	}
}

void Lexer::resetCurrentState() { curr_st = 0; }

bool Lexer::isDigit(char c)
{
	for (int i = 0; i < 10; ++i)
	{
		if (c == (i + '0'))
			return true;
	}
	return false;
}

void Lexer::emptyLexeme() { lexeme = ""; }

string Lexer::getCurrentLexeme() { return lexeme; }

Token Lexer::returnToken(Token t)
{
	previousChar();
	return t;
}

void Lexer::previousChar()
{
	int new_pos = file.tellp();
	new_pos--;
	file.seekp(new_pos, file.beg);
}

bool Lexer::isEOF() { return file.eof(); }

void Lexer::closeFile() { file.close(); }

void Lexer::openFile() { file.open("exampleFile.txt", fstream::in); }

int Lexer::getLine() { return line; }