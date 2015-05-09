#include "stack.h"
#include <climits>

int main (void)
{
    try
    {
        Stack<int> test_stack(LONG_MAX);
        for (int i = 0; i < 11; i++)
        {
	        test_stack.push(i);
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
