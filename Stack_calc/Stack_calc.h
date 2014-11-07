#ifndef STACK_CALC_H_INCLUDED
#include "../Stack/main.c"
#define STACK_CALC_H_INCLUDED
#define MAX_STR_LEN 100
#define MAX_MAX_STACK_SIZE 10000
#define WRONG_NUM -666

int push_from_file(FILE* com_file, struct Stack* stk_p);
int add(struct Stack* stk_p);
int mul(struct Stack* stk_p);
int stack_div(struct Stack* stk_p);
int sub(struct Stack* stk_p);
int stack_sin(struct Stack* stk_p);
int stack_cos(struct Stack* stk_p);
int stack_sqrt(struct Stack* stk_p);
#endif // STACK_CALC_H_INCLUDED
