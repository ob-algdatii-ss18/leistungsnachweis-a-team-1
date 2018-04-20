#include <stdio.h>

int func1() {
	printf("Foo1.c func");
	return 0;
}

int add(int a, int b) {
	return a + b;
}

int complicated(int a) {
	if (a >= 3) {
		return 4;
	}
	else if (a < 0)
	{
		return 1;
	}

	return 0;
}