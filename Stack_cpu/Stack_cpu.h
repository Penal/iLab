#ifndef STACK_CPU_H_INCLUDED
#define STACK_CPU_H_INCLUDED
typedef struct
{
    double* commands_to_execute;
    struct Stack* cpu_data;
    struct Stack* call_stack;
    double a_reg;
    double b_reg;
    double c_reg;
    double d_reg;
    double x_reg;
} Stack_cpu;

const int WRONG_NUM = -13;
const int ONE_ELEMENT = 1;
const int MAX_NUM_OF_CMDS = 30000;
const int MAX_SIZE_OF_DATA = 400;
const int MAX_CALL_STACK_SIZE = 400;
const int SIZE_OF_HEADER = 4;
const double WRONG_COMMAND = -1;
const double IGNORE_COMMAND = -2;
enum {FALSE = 0, TRUE};
int Stack_cpu_errno = 0;
enum
{
    STACK_CPU_ALL_OK = 0,
    STACK_CPU_NULL_CPU_P,
    STACK_CPU_NULL_CPU_DATA_P,
    STACK_CPU_NULL_CMDS_P,
    STACK_CPU_INV_CPU_DATA_STACK,
    STACK_CPU_INV_CALL_STACK
};

enum {
     PUSH_CODE = 1,
     ADD_CODE = 2,
     MUL_CODE = 3,
     SUB_CODE = 4,
     DIV_CODE = 5,
     SIN_CODE = 6,
     COS_CODE = 7,
     SQRT_CODE = 8,
     END_CODE = 9,
     JMP_CODE = 10,
     JA_CODE = 11,
     JAE_CODE = 12,
     JB_CODE = 13,
     JBE_CODE = 14,
     JE_CODE = 15,
     JNE_CODE = 16,
     X_REGIRTER_CODE = 17,
     A_REGIRTER_CODE = 18,
     B_REGIRTER_CODE = 19,
     C_REGIRTER_CODE = 20,
     D_REGIRTER_CODE = 21,
     POP_CODE = 22,
     PUSHX_CODE = 23,
     PUSHA_CODE = 24,
     PUSHB_CODE = 25,
     PUSHC_CODE = 26,
     PUSHD_CODE = 27,
     POPX_CODE = 28,
     POPA_CODE = 29,
     POPB_CODE = 30,
     POPC_CODE = 31,
     POPD_CODE = 32,
     CALL_CODE = 33,
     RET_CODE = 34
};

int Stack_cpu_ctor(Stack_cpu* cpu_p);
int Stack_cpu_dtor(Stack_cpu* cpu_p);
int Stack_cpu_ok(Stack_cpu* cpu_p);
int Stack_cpu_dump(Stack_cpu* cpu_p);
int Stack_cpu_read_cmds_from_file(Stack_cpu* cpu_p, FILE* cmds_file);
int Stack_cpu_execute_cmds(Stack_cpu* cpu_p);
int Stack_cpu_perror(char* bgn_of_msg);
#endif // STACK_CPU_H_INCLUDED
