/**
 *  This is one of the simpiest realization of stack made by me
 *  first-course student of MIPT, Zavodskikh Roman.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#define $(param)  stack_ok(param)

/**
 * \brief This funcution check if stack is OK.
 *
 * This funcution check if stack is OK.
 *  @return 0 if stack is bad
 *  @return 1 if stack is good
 */
int stack_ok(struct Stack* stk_p)
{
    if (!stk_p)
    {
        Stack_errno = null_stack_pointer;
        return 0;
    }
    else if (!stk_p->data)
    {
        Stack_errno = null_data_pointer;
        return 0;
    }
    else if (stk_p->counter > stk_p->max_size)
    {
        Stack_errno = stack_overflow;
        return 0;
    }
    else if (stk_p->counter < 0)
    {
        Stack_errno = stack_underflow;
        return 0;
    }
    return 1;
}

/**
* \brief This function puts info about stack in the console
*
* It tells about counter, max size of stack and its data
* @return 0 always
*/
int stack_dump(struct Stack* stk_p)
{
    stack_perror("Such situation occured");
    printf( "Stack [");
    if ($(stk_p))
    {
        printf( "ok]");
    }
    else
    {
        printf( "BAD!!!]");
    }
    printf( " [0x%lx] |||(GBG means GARBAGE)\n", (unsigned long)stk_p);
    printf( " counter = %40li|\nmax_size = %40li|\n", stk_p->counter, stk_p->max_size);
    printf( "DATA [0x%lx]:\n", (unsigned long)stk_p->data);
    if (stk_p->data)
    {
        for (long i = 0; i < stk_p->max_size;i++)
        {
            printf( "\tdata[%li]=%30.10lg|",i,stk_p->data[i]);
            if (i >= stk_p->counter)
            {
                printf( "(GBG)");
            }
            printf( "\n");
        }
    }
    printf( "END OF DATA\n");
    return 0;
}

/**
* \brief Construct the stack according to the params
*
* Construct the stack according to the params: pointer to stack and max size of it.
* @param stk_p The pointer to stack
* @param max_size The maximum size of stack
* @return 0 always
*/
int stack_ctor(struct Stack* stk_p, long max_size)
{
    stk_p->max_size = max_size;
    stk_p->data = calloc(max_size, sizeof(*(stk_p->data)));
    assert(stk_p->data);
    stk_p->counter = 0;
    return 0;
}

/**
* \brief Destruct the stack
*
* Destruct the stack.
* @param stk_p Pointer to stack
* @return 0 always
*/
int stack_dtor(struct Stack* stk_p)
{
    stk_p->counter = 0;
    free(stk_p->data);
    stk_p->data = NULL;
    stk_p->max_size = 0;
    return 0;
}

/**
* \brief Push some value to stack
*
* Push value add_data to stack
* @param stk_p Pointer to stack
* @param add_data Pushed value
* @return 0 if function ends
* @return nothing if function will be aborted
*/
int stack_push(struct Stack* stk_p, double add_data)
{
    if (!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF STACK_PUSH\n");
        assert(NULL);
    }
    stk_p->data[stk_p->counter] = add_data;
    stk_p->counter++;
    if (!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF STACK_PUSH\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Pops some value from the stack
*
* Pops value that must be popped from stack
* @param stk_p Pointer to stack
* @return rtr_val Value popped from stack
*/
double stack_pop(struct Stack* stk_p)
{
    if (!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF STACK_POP\n");
        assert(NULL);
    }
    stk_p->counter--;
    if (!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE MIDDLE OF STACK_POP\n");
        assert(NULL);
    }

    double rtr_val = stk_p->data[stk_p->counter];
    if (!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF STACK_POP\n");
        assert(NULL);
    }
    return rtr_val;
}

/**
 \brief This function prints error message to console

 This function prints error message to console. This can help you to knwo why program works wrong.
 @param bgn_of_msg String which message will begin from
 @return 0 always
*/
int stack_perror(char* bgn_of_msg)
{
    char* error_msg = ""; //I don't know why, but using calloc and free I get error messages
    assert (error_msg);
    switch (Stack_errno)
    {
        case ok:    error_msg = "Everithing is ok :-)"; break;
        case stack_overflow:    error_msg = "Stack overflow"; break;
        case stack_underflow:   error_msg = "Stack underflow"; break;
        case null_stack_pointer:    error_msg = "Null stack pointer"; break;
        case null_data_pointer: error_msg = "Null data pointer"; break;
    }
    printf("%s:%s\n", bgn_of_msg, error_msg);
    error_msg = NULL;
    return 0;
}
