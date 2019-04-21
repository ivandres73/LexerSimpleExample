#include "Lexer.h"

Lexer::Lexer()
{
    curr_st = 0;
    line = -1;
    //file = fstream("exampleFile.txt", fstream::in);
}

void Lexer::nextChar()
{
    c = file.get();
}

Token Lexer::getToken()
{
	resetCurrentState();

	while (true)
	{
		nextChar();
		// cout << "state: " << curr_st << endl;
		// cout << "c is " << c << endl;

    	switch(curr_st)
    	{
			case 0:
				if (file.eof())
					return returnToken(Token::end_file);
				else if (c == '\n')
					line++;
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
				break;
			case 1:
				if (isDigit(c))
					continue;
				else if (c == '.')
					curr_st = 3;
				else if (file.eof())
					curr_st = 2;
				else
					curr_st = 2;
				break;
			case 2:
				return returnToken(Token::int_const);
			case 3:
				if (isDigit(c))
					continue;
				else if (file.eof())
					curr_st = 4;
				else
					curr_st = 4;
				break;
			case 4:
				return returnToken(Token::float_const);
			case 5:
				return returnToken(Token::add);
			case 6:
				return returnToken(Token::sub);
			case 7:
				return returnToken(Token::multi);
			case 8:
				return returnToken(Token::divi);
			case 9:
				if (c == '=')
					curr_st = 11;
				else if (file.eof())
					curr_st = 10;
				else
					curr_st = 10;
				break;
			case 10:
				return returnToken(Token::greater_than);
			case 11:
				return returnToken(Token::greater_equal);
			case 12:
				if (c == '=')
					curr_st = 14;
				else if (file.eof())
					curr_st = 13;
				else
					curr_st = 13;
				break;
			case 13:
				return returnToken(Token::lesser_than);
			case 14:
				return returnToken(Token::lesser_equal);
			case 15:
				return returnToken(Token::open_parens);
			case 16:
				return returnToken(Token::close_parens);
			case 17:
				if (c == '=')
					curr_st = 18;
				break;
			case 18:
				return returnToken(Token::is_equal);
			case 19:
				if (c == '=')
					curr_st = 20;
				break;
			case 20:
				return returnToken(Token::different);
			case 21:
				if (c == '/')
					curr_st = 22;
				else if (c == '*')
					curr_st = 23;
				else if (file.eof())
					curr_st = 8;
				else
					curr_st = 8;
				break;
			case 22:
				if (c == '\n')
					curr_st = 0;
				else if (file.eof())
					continue;
				else
					continue;
				break;
			case 23:
				if (c == '*')
					curr_st = 24;
				else if (file.eof())
					continue;
				else
					continue;
			case 24:
				if (c == '*')
					continue;
				else if (c == '/')
					curr_st = 0;
				else if (file.eof())
					curr_st = 23;
				else
					curr_st = 23;
				break;
    	}
    	// cout << "file posi: " << file.tellp() << endl;
    	// cout << "-------------------------" << endl;
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