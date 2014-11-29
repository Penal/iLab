#ifndef STACK_CPU_H_INCLUDED
#define STACK_CPU_H_INCLUDED

#define DEF_CMD(cmd_num, cmd_code, argc, code) cmd_code##_NUM = cmd_num,
enum
{
    #include "../Stack_cpu_cmds/cmds.h"
    MAX_CMD
};
#undef DEF_CMD

typedef struct
{
    double* commands_to_execute;
    struct Stack* cpu_data;
    struct Stack* call_stack;
    double a_reg;
    double b_reg;
    double c_reg;
    double d_reg;
} Stack_cpu;

const int WRONG_NUM = -13;
const int ONE_ELEMENT = 1;
const int MAX_NUM_OF_CMDS = 30000;
const int MAX_SIZE_OF_DATA = 20;
const int MAX_CALL_STACK_SIZE = 20;
const int SIZE_OF_HEADER = 4;
const int MAX_FILENAME_LEN = 70;

enum {FALSE = 0, TRUE};

int Stack_cpu_errno = 0;
enum Stack_cpu_errno_states
{
    STACK_CPU_ALL_OK = 0,
    STACK_CPU_NULL_CPU_P,
    STACK_CPU_NULL_CPU_DATA_P,
    STACK_CPU_NULL_CMDS_P,
    STACK_CPU_INV_CPU_DATA_STACK,
    STACK_CPU_INV_CALL_STACK
};

int Stack_cpu_ctor(Stack_cpu* cpu_p);
int Stack_cpu_dtor(Stack_cpu* cpu_p);
int Stack_cpu_ok(Stack_cpu* cpu_p);
int Stack_cpu_dump(Stack_cpu* cpu_p);
int Stack_cpu_read_cmds_from_file(Stack_cpu* cpu_p, FILE* cmds_file);
int Stack_cpu_execute_cmds(Stack_cpu* cpu_p);
int Stack_cpu_perror(char* bgn_of_msg);
#endif // STACK_CPU_H_INCLUDED
