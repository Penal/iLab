#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../Stack/main.c"
#include "Stack_cpu.h"
#define $$(param ) Stack_cpu_ok(param)
#define CPU_ERR(cpu_p, msg) \
{\
    printf(msg);\
    Stack_cpu_dump(cpu_p); \
    assert((NULL)); \
}

#define Validate_CPU(cpu_p, msg) if(!$$(cpu_p)) \
{ \
    CPU_ERR(cpu_p, msg);\
}

int main()
{
    Stack_cpu* CPU = (Stack_cpu*)calloc(ONE_ELEMENT, sizeof(*CPU));
    assert(CPU);
    Stack_cpu_ctor(CPU);
    FILE* cmds_file = fopen("commands_num.txt", "rb");
    Stack_cpu_read_cmds_from_file(CPU, cmds_file);
    Stack_cpu_execute_cmds(CPU);
    Stack_cpu_dtor(CPU);
    free(CPU);
    CPU = NULL;
    fclose(cmds_file);
    cmds_file = NULL;
    return 0;
}

int Stack_cpu_ctor(Stack_cpu* cpu_p)
{
    cpu_p->commands_to_execute = (double*)calloc(MAX_NUM_OF_CMDS,
        sizeof(*(cpu_p->commands_to_execute)));
    assert(cpu_p->commands_to_execute);
    cpu_p->cpu_data = (struct Stack*)calloc(ONE_ELEMENT, sizeof(*cpu_p->cpu_data));
    stack_ctor(cpu_p->cpu_data, MAX_SIZE_OF_DATA);
    assert(cpu_p->cpu_data);
    cpu_p->a_reg = cpu_p->b_reg = cpu_p->c_reg = cpu_p->d_reg = cpu_p->x_reg = 0;
    cpu_p->call_stack = (struct Stack*)calloc(ONE_ELEMENT, sizeof(*cpu_p->call_stack));
    stack_ctor(cpu_p->call_stack, MAX_CALL_STACK_SIZE);
    assert(cpu_p->call_stack);
    return 0;
}

int Stack_cpu_ok(Stack_cpu* cpu_p)
{
    if(!cpu_p)
    {
        Stack_cpu_errno = STACK_CPU_NULL_CPU_P;
        return FALSE;
    }
    else if (!(cpu_p->cpu_data))
    {
        Stack_cpu_errno = STACK_CPU_NULL_CPU_DATA_P;
        return FALSE;
    }
    else if (!(cpu_p->commands_to_execute))
    {
        Stack_cpu_errno = STACK_CPU_NULL_CMDS_P;
        return FALSE;
    }
    else if (!stack_ok(cpu_p->cpu_data))
    {
        Stack_cpu_errno = STACK_CPU_INV_CPU_DATA_STACK;
        return FALSE;
    }
    else if (!stack_ok(cpu_p->call_stack))
    {
        Stack_cpu_errno = STACK_CPU_INV_CALL_STACK;
        return FALSE;
    }
    Stack_cpu_errno = STACK_CPU_ALL_OK;
    return TRUE;
}

int Stack_cpu_dump(Stack_cpu* cpu_p)
{
    Stack_cpu_perror("Such situation occured");
    printf( "STACK_CPU [");
    if($$(cpu_p))
    {
        printf( "ok]");
    }
    else
    {
        printf( "BAD!!!]");
    }
    printf( " [0x%lx]\n", (unsigned long)cpu_p);
    printf( "\tREGISTER A:%40.7lg||\n", cpu_p->a_reg);
    printf( "\tREGISTER B:%40.7lg||\n", cpu_p->b_reg);
    printf( "\tREGISTER C:%40.7lg||\n", cpu_p->c_reg);
    printf( "\tREGISTER D:%40.7lg||\n", cpu_p->d_reg);
    printf( "\tREGISTER X:%40.7lg||\n", cpu_p->x_reg);
    printf( "\t\t------CPU DATA------\n");
    stack_dump(cpu_p->cpu_data);
    printf( "\t\t------CALL STACK------\n");
    stack_dump(cpu_p->call_stack);
    return 0;
}

int Stack_cpu_dtor(Stack_cpu* cpu_p)
{
    stack_dtor(cpu_p->call_stack);
    cpu_p->call_stack = NULL;
    free(cpu_p->commands_to_execute);
    cpu_p->commands_to_execute = NULL;
    stack_dtor(cpu_p->cpu_data);
    free(cpu_p->cpu_data);
    cpu_p->cpu_data = NULL;
    cpu_p->a_reg = cpu_p->b_reg = cpu_p->c_reg =
    cpu_p->d_reg = cpu_p->x_reg = WRONG_NUM;
    return 0;
}

int Stack_cpu_perror(char* bgn_of_msg)
{
    char* error_msg="";
    assert (error_msg);
    switch (Stack_errno)
    {
        case STACK_CPU_ALL_OK:    error_msg = "Everithing is ok :-)"; break;
        case STACK_CPU_NULL_CPU_P:    error_msg = "Invalid stack CPU pointer"; break;
        case STACK_CPU_NULL_CMDS_P:   error_msg = "Invalid stack CPU commands pointer";
         break;
        case STACK_CPU_INV_CPU_DATA_STACK:    error_msg = "Invalid data stack in stack CPU";
         break;
        case STACK_CPU_NULL_CPU_DATA_P: error_msg = "Null stack CPU data pointer"; break;
        case STACK_CPU_INV_CALL_STACK: error_msg = "Invalid call stack in stack CPU" ; break;
        default:                error_msg = "Some unexpected situation. Tell developer to add it";
         break;
    }
    printf("%s:%s\n", bgn_of_msg, error_msg);
    error_msg = NULL;
    return 0;
}

int Stack_cpu_read_cmds_from_file(Stack_cpu* cpu_p, FILE* cmds_file)
{
    Validate_CPU(cpu_p, "Invalid CPU in the beginning of commands reading\n");
    fseek(cmds_file, 0, SEEK_END);
    long file_length = ftell(cmds_file);
    file_length -= SIZE_OF_HEADER*sizeof(*(cpu_p->commands_to_execute)); //skipping the header
    fseek(cmds_file, SIZE_OF_HEADER*sizeof(*(cpu_p->commands_to_execute)), SEEK_SET);
    fread(cpu_p->commands_to_execute, sizeof(*(cpu_p->commands_to_execute)),
     file_length/sizeof(*(cpu_p->commands_to_execute)), cmds_file);
    Validate_CPU(cpu_p, "Invalid CPU in the end of commands reading\n");
    return 0;
}

int Stack_cpu_execute_cmds(Stack_cpu* cpu_p)
{
    Validate_CPU(cpu_p, "Invalid CPU in the beginning of commands executing\n");
    long i = 0;
    for (i = 0;cpu_p->commands_to_execute[i] != END_CODE; i++)
    {
        //execute cpu_p->commands_to_execute[i]
        int cmd_code = cpu_p->commands_to_execute[i];
        if (cmd_code != IGNORE_COMMAND && cmd_code != 0)
        {
            if (cmd_code == PUSH_CODE)
            {
                i++;
                stack_push(cpu_p->cpu_data, cpu_p->commands_to_execute[i]);
                continue;
            }
            else if (cmd_code == JMP_CODE ||
                cmd_code == CALL_CODE)
            {
                i++;
                i = cpu_p->commands_to_execute[i] - 1; //-1 because it'll be i++ next line
                if (cmd_code == CALL_CODE)
                {
                    stack_push(cpu_p->call_stack, i+1);
                }
                continue;
            }
            else if (cmd_code == JA_CODE ||
            cmd_code == JAE_CODE ||
            cmd_code == JB_CODE ||
            cmd_code == JBE_CODE ||
            cmd_code == JE_CODE ||
            cmd_code == JNE_CODE
            )
            {
                int prev_cmd_code = cmd_code;
                i++;
                double upper = stack_pop(cpu_p->cpu_data);
                double lower = stack_pop(cpu_p->cpu_data);
                if ( (upper > lower && prev_cmd_code == JA_CODE) ||
                    (upper >= lower && prev_cmd_code == JAE_CODE) ||
                    (upper < lower && prev_cmd_code == JB_CODE) ||
                    (upper <= lower && prev_cmd_code == JBE_CODE) ||
                    (upper == lower && prev_cmd_code == JE_CODE) ||
                    (upper != lower && prev_cmd_code == JNE_CODE))
                {
                    i = cpu_p->commands_to_execute[i] - 1;
                }
                stack_push(cpu_p->cpu_data, lower);
                stack_push(cpu_p->cpu_data, upper);
                Stack_cpu_dump(cpu_p);
                continue;
            }
            else if (cmd_code == ADD_CODE ||
                    cmd_code == SUB_CODE ||
                    cmd_code == MUL_CODE ||
                    cmd_code == DIV_CODE)
            {
                double upper = stack_pop(cpu_p->cpu_data);
                double lower = stack_pop(cpu_p->cpu_data);
                if(cmd_code==ADD_CODE)
                    stack_push(cpu_p->cpu_data, lower+upper);
                if(cmd_code==SUB_CODE)
                    stack_push(cpu_p->cpu_data, lower-upper);
                if(cmd_code==MUL_CODE)
                    stack_push(cpu_p->cpu_data, lower*upper);
                if(cmd_code==DIV_CODE)
                {
                    if (upper == 0)
                    {
                        CPU_ERR(cpu_p, "Division by zero\n");
                    }
                    else
                    {
                        stack_push(cpu_p->cpu_data, lower/upper);
                    }
                }
            }
            else if (cmd_code == SQRT_CODE ||
                cmd_code == SIN_CODE ||
                cmd_code == COS_CODE)
            {
                if(cmd_code==SIN_CODE)
                    stack_push(cpu_p->cpu_data, sin( stack_pop(cpu_p->cpu_data) ));
                if(cmd_code==COS_CODE)
                    stack_push(cpu_p->cpu_data, cos( stack_pop(cpu_p->cpu_data) ));
                if(cmd_code==SQRT_CODE)
                {
                    double temp1 = stack_pop(cpu_p->cpu_data);
                    if (temp1<0)
                    {
                        CPU_ERR(cpu_p, "Taking root of negative number\n");
                    }
                }
            }
            else if(cmd_code == POP_CODE)
            {
                printf("%lg\n", stack_pop(cpu_p->cpu_data));
            }
            else if(cmd_code >= PUSHX_CODE && cmd_code <= PUSHD_CODE)
            {
                if(cmd_code == PUSHX_CODE)
                    stack_push(cpu_p->cpu_data,cpu_p->x_reg);
                if(cmd_code == PUSHA_CODE)
                    stack_push(cpu_p->cpu_data,cpu_p->a_reg);
                if(cmd_code == PUSHB_CODE)
                    stack_push(cpu_p->cpu_data,cpu_p->b_reg);
                if(cmd_code == PUSHC_CODE)
                    stack_push(cpu_p->cpu_data,cpu_p->c_reg);
                if(cmd_code == PUSHD_CODE)
                    stack_push(cpu_p->cpu_data,cpu_p->d_reg);
            }
            else if(cmd_code >= POPX_CODE && cmd_code <= POPD_CODE)
            {
                if(cmd_code == POPX_CODE)
                    cpu_p->x_reg=stack_pop(cpu_p->cpu_data);
                if(cmd_code == POPA_CODE)
                    cpu_p->a_reg=stack_pop(cpu_p->cpu_data);
                if(cmd_code == POPB_CODE)
                    cpu_p->b_reg=stack_pop(cpu_p->cpu_data);
                if(cmd_code == POPC_CODE)
                    cpu_p->c_reg=stack_pop(cpu_p->cpu_data);
                if(cmd_code == POPD_CODE)
                    cpu_p->d_reg=stack_pop(cpu_p->cpu_data);
            }
            else if (cmd_code == RET_CODE)
            {
                i = stack_pop(cpu_p->call_stack) - 1; //-1 because it'll be i++
            }
        }
    }
    Validate_CPU(cpu_p, "Invalid CPU in the end of commands executing\n");
    return 0;
}
