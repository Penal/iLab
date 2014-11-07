/**
* Assembler-like calculator made by me
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "Stack_calc.h"

int main()
{
    FILE* com_file = fopen("commands.txt", "r");
    char* command = calloc(MAX_STR_LEN, sizeof(command[0]));
    struct Stack stk = {};
    stack_ctor(&stk,MAX_MAX_STACK_SIZE);
    while (fscanf(com_file,"%s", command) != EOF)
    {
        if (strcmp(command, "push") == 0)
        {
            push_from_file(com_file, &stk);
        }
        else if (strcmp(command, "add") == 0)
        {
            add(&stk);
        }
        else if (strcmp(command, "mul") == 0)
        {
            mul(&stk);
        }
        else if (strcmp(command, "sub") == 0)
        {
            sub(&stk);
        }
        else if (strcmp(command, "div") == 0)
        {
            stack_div(&stk);
        }
        else if (strcmp(command, "sin") == 0)
        {
            stack_sin(&stk);
        }
        else if (strcmp(command, "cos") == 0)
        {
            stack_cos(&stk);
        }
        else if (strcmp(command, "sqrt") == 0)
        {
            stack_sqrt(&stk);
        }
        else if (strcmp(command, "end") == 0)
        {
            break;
        }
    }
    fclose(com_file);
    com_file = NULL;
    if (stk.counter == 1)
    {
        FILE* res_file = fopen("res.txt", "w");
        fprintf(res_file, "%lg\n", stack_pop(&stk));
        fclose(res_file);
        res_file = NULL;
    }
    else
    {
        stack_dump(&stk);
        printf("Stack has not one element. It musnt not be so:\n");
    }
    return 0;
}

/**
* \brief Push number from file in stack
*
* @param stk_p Pointer to stack
* @param com_file File that contains pushable number
* @return 0 always
*/
int push_from_file(FILE* com_file, struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF push_from_file!!!\n");
        assert(NULL);
    }
    double number = WRONG_NUM;
    fscanf(com_file, "%lg", &number);
    stack_push(stk_p, number);
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF push_from_file!!!\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Calculate sum of two upper numbers of stack and pushes it in stack
*
* @param stk_p Pointer to stack
* @return 0 always
*/
int add(struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF add!!!\n");
        assert(NULL);
    }
    double operand1 = WRONG_NUM;
    double operand2 = WRONG_NUM;
    operand1 = stack_pop(stk_p);
    operand2 = stack_pop(stk_p);
    stack_push(stk_p, operand1+operand2);
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF add!!!\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Calculate product of two upper numbers of stack and pushes it in stack
*
* @param stk_p Pointer to stack
* @return 0 always
*/
int mul(struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF mul!!!\n");
        assert(NULL);
    }
    double operand1 = WRONG_NUM;
    double operand2 = WRONG_NUM;
    operand1 = stack_pop(stk_p);
    operand2 = stack_pop(stk_p);
    stack_push(stk_p, operand1*operand2);
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF mul!!!\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Calculate division of two upper numbers of stack and pushes it in stack
*
* @param stk_p Pointer to stack
* @return 0 always
*/
int stack_div(struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF stack_div!!!\n");
        assert(NULL);
    }
    double operand1 = WRONG_NUM;
    double operand2 = WRONG_NUM;
    operand1 = stack_pop(stk_p);
    operand2 = stack_pop(stk_p);
    if (operand2 == 0)
    {
        printf("DIVISION BY ZERO IN stack_div\n");
        assert(NULL);
    }
    stack_push(stk_p, operand1/operand2);
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF stack_div!!!\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Calculate subtraction of two upper numbers of stack and pushes it in stack
*
* @param stk_p Pointer to stack
* @return 0 always
*/
int sub(struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF sub!!!\n");
        assert(NULL);
    }
    double operand1 = WRONG_NUM;
    double operand2 = WRONG_NUM;
    operand1 = stack_pop(stk_p);
    operand2 = stack_pop(stk_p);
    stack_push(stk_p, operand1-operand2);
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF sub!!!\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Calculate sin of upper number of stack and pushes it in stack
*
* @param stk_p Pointer to stack
* @return 0 always
*/
int stack_sin(struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF stack_sin!!!\n");
        assert(NULL);
    }
    double operand1 = WRONG_NUM;
    operand1 = stack_pop(stk_p);
    stack_push(stk_p, sin(operand1));
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF stack_sin!!!\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Calculate cos of upper number of stack and pushes it in stack
*
* @param stk_p Pointer to stack
* @return 0 always
*/
int stack_cos(struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF stack_cos!!!\n");
        assert(NULL);
    }
    double operand1 = WRONG_NUM;
    operand1 = stack_pop(stk_p);
    stack_push(stk_p, cos(operand1));
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF stack_cos!!!\n");
        assert(NULL);
    }
    return 0;
}

/**
* \brief Calculate square root of upper number of stack and pushes it in stack
*
* @param stk_p Pointer to stack
* @return 0 always
*/
int stack_sqrt(struct Stack* stk_p)
{
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE BEGINNING OF stack_sqrt!!!\n");
        assert(NULL);
    }
    double operand1 = WRONG_NUM;
    operand1 = stack_pop(stk_p);
    if (operand1 < 0)
    {
        printf("TRYING OF TAKING ROOT OF NEGATIVE NUMBER\n");
        assert(NULL);
    }
    stack_push(stk_p, sqrt(operand1));
    if(!$(stk_p))
    {
        stack_dump(stk_p);
        printf("INVALID STACK IN THE END OF stack_sqrt!!!\n");
        assert(NULL);
    }
    return 0;
}
