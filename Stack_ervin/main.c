#include <stdio.h>
#include <stdlib.h>
#include "my_stack.h"

int main (void)
{
    //Ervin, insert your code here;
    my_stack_double* stk_p = my_stack_double_new(10);
    for (int i = 0; i < 32; i++)
    {
        my_stack_double_push(stk_p, 53);
    }
    for (int i = 0; i < 27; i++)
    {
        my_stack_double_pop(stk_p);
    }
    my_stack_double_dump(stk_p);
    my_stack_double_delete(stk_p);
    return 0;
}
