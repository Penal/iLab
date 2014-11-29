#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Stack_disasm.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stdout, "Invalid number of args, it should be file name, and nothing more\n");
        exit(0);
    }

    char* filename = (char*)calloc(MAX_FILENAME_LEN, sizeof(*filename));
    assert(filename);
    strcpy(filename, argv[1]);

    FILE* commands_file = fopen(filename, "rb");
    assert(commands_file);

    double* commands_buffer = (double*)calloc(MAX_STACK_ASM_CMDS_BUFFER_SIZE,
        sizeof(*commands_buffer));
    assert(commands_buffer);

    double* const adress_of_commands_buffer = commands_buffer;
    write_commands_to_buffer(commands_buffer,commands_file);
    commands_buffer = adress_of_commands_buffer;
    fclose(commands_file);

    commands_file = fopen(get_cmd_file_name(filename), "w");

    free(filename);
    filename = NULL;

    assert(commands_file);
    write_commands_to_file(commands_buffer, commands_file);

    fclose(commands_file);
    commands_file = NULL;
    free(commands_buffer);
    commands_buffer = NULL;
    return 0;
}

int write_commands_to_buffer(double* commands_buffer, FILE* commands_file)
{
    fseek(commands_file, 0, SEEK_END);
    long file_length = ftell(commands_file);
    const int size = sizeof(*commands_buffer);

    file_length -= SIZE_OF_HEADER*size; //skipping the header

    fseek(commands_file, SIZE_OF_HEADER*size, SEEK_SET);
    fread(commands_buffer, size, file_length/size, commands_file);
    return 0;
}

int write_commands_to_file(double* commands_buffer, FILE* commands_file)
{
    assert(commands_buffer);
    assert(commands_file);

    while ((int)*commands_buffer != END_OF_BUFFER_NUM && (int)*commands_buffer != 0)
    {
      #define DEF_CMD(cmd_num, cmd_code, argc, code) if(*commands_buffer == cmd_num)\
      {\
            fprintf(commands_file, "%s", get_cmd_name_by_code(*commands_buffer));\
            commands_buffer++;\
            \
            for (int i = 0; i < argc; i++)\
            {\
                fprintf(commands_file, " %i", (int)*commands_buffer);\
                commands_buffer++;\
            }\
            \
            fprintf(commands_file, "\n");\
        }
        #include "../Stack_cpu_cmds/cmds.h"
        #undef DEF_CMD
    }
    return 0;
}

char* get_cmd_name_by_code(double cmd_code)
{
    switch ((int)cmd_code)
    {
        #define DEF_CMD(cmd_num, cmd_code, argc, code) case cmd_code##_NUM: return #cmd_code; break;
        #include "../Stack_cpu_cmds/cmds.h"
        #undef DEF_CMD
        default: printf("Some unexpected instruction\n"); break;
    }
    return NULL;
}

char* get_cmd_file_name(char* bin_file_name)
{
    char* rtr_val = bin_file_name;
    long length = strlen(bin_file_name);
    //change ".bin" to ".txt"
    rtr_val[length-3]='t';
    rtr_val[length-2]='x';
    rtr_val[length-1]='t';
    return rtr_val;
}
