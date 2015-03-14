#include <iostream>
#include <cstring>
#include "stack.h"

int main (void)
{
	using std::cout;
	using std::endl;

	Stack<double> s1(5);
	for(int i = 0; i < 1200; i++)
	{
		s1.push( (i+1)*1.1);
	}
	s1.dump();

	return 0;
}
