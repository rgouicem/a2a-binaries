#include <stdlib.h>
#include <time.h>

int add(int a, int b)
{
	return a + b;
}


int main()
{
	int a, b, c;

	srand(time(NULL));
	a = rand();
	b = rand();

	c = add(a, b);

	return c;
}
