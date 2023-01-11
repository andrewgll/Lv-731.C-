// blank_lines 1,  comment_lines 9, code_lines  10

int main()
{
	// comment
	/* multiline comment */
	int i = 1;
	int x = 5; // comment after code
	x++; /* multiline comment after code */
	/* multiline code before code */ x++;
	x = i;
	// comment after slash
	x;	/* line 1
	line 3 */ return 0;
}