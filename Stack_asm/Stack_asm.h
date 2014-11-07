#ifndef STACK_ASM_H_INCLUDED
#define STACK_ASM_H_INCLUDED
const int MAX_STRING_LENGTH = 20;
const int MAX_STACK_ASM_STACK_BUFFER_SIZE = 100000;
const double WRONG_COMMAND = -1;
const double IGNORE_COMMAND = -2;
const int WRONG_NUM = -13;
const int ONE_ELEMENT = 1;
const int SIZE_OF_HEADER = 4;
const int WRONG_CHAR = -1;
const int NUM_OF_MARKS = 10;

const int TRUE = 1;
const int FALSE = 0;

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

int write_commands_to_buffer(double* commands_buffer, FILE* commands_file,
      double* array_of_marks);
int write_commands_to_file(double* commands_buffer, FILE* commands_file);
int fill_array_of_marks(double* array_of_marks, FILE* commands_file);
double get_code_by_cmd_name(char* cmd);
#endif // STACK_ASM_H_INCLUDED
