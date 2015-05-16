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
	    for (int i = 0; i < 13; i++)
        {
    	    test_stack.pop();
        }
    }
    catch (Stack_crushed exc)
    {
        //Here should be actions to retrieve the exception... But I don't know what to do, actually
        cerr << "ATTENTION!!! STACK CRUSHED!!! PROGRAM HAS LOST ITS STABILITY!!!\n";
    }
    catch (int num)
    {
        cerr << "I don\'t know why but there was catched number " << num << endl;
    }
    catch (char* str)
    {
        if (str)
        {
            cerr << "I don\'t know why but there was catched string " << str << endl;
        }
        else
        {
            cerr << "I don\'t know why but there was cathced nullptr of string\n";
        }
    }
    catch (...)
    {
        cerr << "T\'was cathced I don\'t know even what\n";
    }
	return 0;
}
