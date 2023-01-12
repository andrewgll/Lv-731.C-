// blank: 1, code: 6, comments: 4, code with comments: 6, total: 17

int main()
{
	// comment
	/* multiline comment */
	int i = 1;
	int x = 5; // comment after code
	x++; /* multiline comment after code */
	/* multiline code before code */ x++;
	x =
	i
	/ // comment after slash
	x;	/* line 1
	
	line 3 */return 0;
}