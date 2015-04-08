#include "stack.h"

int main (void)
{
	Stack<int> test_stack(5);
	for (int i = 0; i < 11; i++)
	{
	    test_stack.push(i+1);
	}
	for (int i = 0; i < 13; i++)
	{
	    test_stack.pop();
	}
	return 0;
}
