#include "stack.h"

int main (void)
{
	Stack<int> test_stack(5);
	for (int i = 0; i < 15; i++)
	{
	    test_stack.push(i+1);
	}
	for (int i = 0; i < 15; i++)
	{
	    test_stack.pop();
	}
	return 0;
}
