#include "stack.h"

int main (void)
{
    try
    {
        Stack<int> test_stack;
        for (int i = 0; i < 11; i++)
        {
	        test_stack.push(i+1);
        }
	    for (int i = 0; i < 12; i++)
        {
    	    test_stack.pop();
        }
    }
    catch (Stack_crushed exc)
    {
        //Here should be actions to retrieve the exception... But I don't know what to do, actually
        cerr << "ATTENTION!!! STACK CRUSHED!!! PROGRAM HAS LOST ITS STABILITY!!!\n";
    }
	return 0;
}
