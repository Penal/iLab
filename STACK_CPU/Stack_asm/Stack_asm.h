#ifndef STACK_ASM_H_INCLUDED
#define STACK_ASM_H_INCLUDED

#define DEF_CMD(cmd_num, cmd_code, argc, code) cmd_code##_NUM = cmd_num,
enum
{
    #include "../Stack_cpu_cmds/cmds.h"
    MAX_CMD
};
#undef DEF_CMD

const int MAX_STRING_LENGTH = 20;
const int MAX_STACK_ASM_STACK_BUFFER_SIZE = 100000;
const int WRONG_NUM = -13;
const int ONE_ELEMENT = 1;
const int SIZE_OF_HEADER = 4;
const int WRONG_CHAR = -1;
const int NUM_OF_MARKS = 10;
const int MAX_FILENAME_LEN = 70;

const int TRUE = 1;
const int FALSE = 0;

int write_commands_to_buffer(double* commands_buffer, FILE* commands_file,
      double* array_of_marks);
int write_commands_to_file(double* commands_buffer, FILE* commands_file);
int fill_array_of_marks(double* array_of_marks, FILE* commands_file);
double get_code_by_cmd_name(char* cmd, double* array_of_marks);
char* bin_file_name(char* cmds_file_name);
#endif // STACK_ASM_H_INCLUDED
