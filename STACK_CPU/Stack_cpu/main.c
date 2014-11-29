#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "../Stack/main.c"
#include "Stack_cpu.h"

#define $(type, param)  type##_ok(param)

#define CPU_ERR(cpu_p, msg) \
{\
    printf(msg);\
    Stack_cpu_dump(cpu_p); \
    assert(NULL); \
}

#define Validate_CPU(cpu_p, msg) if(!$(Stack_cpu,cpu_p)) \
{ \
    CPU_ERR(cpu_p, msg);\
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Invalid number of args, it should be file name and nothing more\n");
        exit(0);
    }

    Stack_cpu* CPU = (Stack_cpu*)calloc(ONE_ELEMENT, sizeof(*CPU));
    assert(CPU);
    Stack_cpu_ctor(CPU);

    char* filename = (char*)calloc(MAX_FILENAME_LEN, sizeof(*filename));
    assert(filename);
    strcpy(filename, argv[1]);

    FILE* cmds_file = fopen(filename, "rb");
    assert(cmds_file);
    Stack_cpu_read_cmds_from_file(CPU, cmds_file);
    Stack_cpu_execute_cmds(CPU);
    Stack_cpu_dtor(CPU);

    free(CPU);
    CPU = NULL;
    fclose(cmds_file);
    cmds_file = NULL;
    free(filename);
    filename = NULL;
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

    cpu_p->a_reg = cpu_p->b_reg = cpu_p->c_reg = cpu_p->d_reg = 0;

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
    if($(Stack_cpu, cpu_p))
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

    printf( "\t\t------CPU DATA------\n");
    stack_dump(cpu_p->cpu_data);

    printf( "\t\t------CALL STACK------\n");
    stack_dump(cpu_p->call_stack);
    return 0;
}

int Stack_cpu_dtor(Stack_cpu* cpu_p)
{
    stack_dtor(cpu_p->call_stack);
    free(cpu_p->call_stack);

    cpu_p->call_stack = NULL;
    free(cpu_p->commands_to_execute);

    cpu_p->commands_to_execute = NULL;
    stack_dtor(cpu_p->cpu_data);

    free(cpu_p->cpu_data);
    cpu_p->cpu_data = NULL;

    cpu_p->a_reg = cpu_p->b_reg = cpu_p->c_reg =
    cpu_p->d_reg = WRONG_NUM;

    return 0;
}

int Stack_cpu_perror(char* bgn_of_msg)
{
    char* error_msg="";
    assert (error_msg);
    switch (Stack_errno)
    {
        case STACK_CPU_ALL_OK:            error_msg = "Everithing is ok :-)";                          break;
        case STACK_CPU_NULL_CPU_P:        error_msg = "Invalid stack CPU pointer";                     break;
        case STACK_CPU_NULL_CMDS_P:       error_msg = "Invalid stack CPU commands pointer";            break;
        case STACK_CPU_INV_CPU_DATA_STACK: error_msg = "Invalid data stack in stack CPU";                break;
        case STACK_CPU_NULL_CPU_DATA_P:    error_msg = "Null stack CPU data pointer";                   break;
        case STACK_CPU_INV_CALL_STACK:     error_msg = "Invalid call stack in stack CPU" ;                break;
        default:                          error_msg = "Some unexpected situation. Ask developer to add it"; break;
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
    int size = sizeof(*(cpu_p->commands_to_execute));
    file_length -= SIZE_OF_HEADER*size; //skipping the header

    fseek(cmds_file, SIZE_OF_HEADER*size, SEEK_SET);
    fread(cpu_p->commands_to_execute, size, file_length/size, cmds_file);

    Validate_CPU(cpu_p, "Invalid CPU in the end of commands reading\n");
    return 0;
}

int Stack_cpu_execute_cmds(Stack_cpu* cpu_p)
{
    Validate_CPU(cpu_p, "Invalid CPU in the beginning of commands executing\n");

    long i = 0;
    for (i = 0;cpu_p->commands_to_execute[i] != END_NUM; i++)
    {
        //changing something in this cycle
        //needs changing in cmds.h
        int command_code = cpu_p->commands_to_execute[i];
        if (command_code != 0)
        {
            #define DEF_CMD(cmd_num, cmd_code, argc, code) if (command_code==cmd_num)\
            {\
            code\
            continue;}
            #include "../Stack_cpu_cmds/cmds.h"
            #undef DEF_CMD
        }
    }

    Validate_CPU(cpu_p, "Invalid CPU in the end of commands executing\n");
    return 0;
}
