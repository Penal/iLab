#ifndef STACK_DISASM_H_INCLUDED
#define STACK_DISASM_H_INCLUDED

#define DEF_CMD(cmd_num, cmd_code, argc, code) cmd_code##_NUM = cmd_num,
enum
{
    #include "../Stack_cpu_cmds/cmds.h"
    MAX_CMD
};
#undef DEF_CMD

enum {FALSE = 0, TRUE = 1};

const int MAX_STRING_LENGTH = 20;
const int MAX_STACK_ASM_CMDS_BUFFER_SIZE = 100000;
const int WRONG_NUM = -13;
const int ONE_ELEMENT = 1;
const int SIZE_OF_HEADER = 4;
const int WRONG_CHAR = -1;
const int MAX_FILENAME_LEN = 70;

int write_commands_to_buffer(double* commands_buffer, FILE* commands_file);
int write_commands_to_file(double* commands_buffer, FILE* commands_file);
char* get_cmd_name_by_code(double cmd_code);
char* get_cmd_file_name(char* bin_file_name);
#endif // STACK_DISASM_H_INCLUDED
