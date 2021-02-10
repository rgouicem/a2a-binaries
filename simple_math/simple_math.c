#ifdef DEBUG
#include <stdio.h>
#else
#define printf(...) ;
#endif

int main(int argc, char **argv)
{
	char op;
	int v0, v1, res;

	if (argc != 4)
		return -1;

	op = argv[1][0];
	v0 = argv[2][0] - '0';
	v1 = argv[3][0] - '0';

	printf("op: %c\n"
	       "v0: %d\n"
	       "v1: %d\n",
	       op, v0, v1);

	if (op == '+')
		res = v0 + v1;
	else if (op == '-')
		res = v0 - v1;
	else if (op == '*')
		res = v0 * v1;
	else if (op == '/')
		res = v0 / v1;
	else
		res = -1;

	return res;
}
