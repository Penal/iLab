#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
/**
* This struct contains typical stack
*/
struct Stack
{
    double* data; /**< array of data that stack contains*/
    long counter; /**< counter of elements that stack contains*/
    long max_size; /**< maximum size of stack*/
};

int Stack_errno = 0;
int const MAX_STR_LEN = 100;
enum {ok = 0, stack_overflow = 1, stack_underflow=2, null_stack_pointer=3, null_data_pointer=4};

int stack_ctor(struct Stack* stk_p, long max_size);
int stack_dtor(struct Stack* stk_p);
int stack_ok(struct Stack* stk_p);
int stack_dump(struct Stack* stk_p);
int stack_push(struct Stack* stk_p, double add_data);
double stack_pop(struct Stack* stk_p);
int stack_perror(char* bgn_of_msg);

#endif // STACK_H_INCLUDED
