/**
 Stack assembler (commands version 1.0)
 Zavodskikh Roman 412 group of MIPT
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Stack_asm.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Invalid number of args: it should be file name and nothing more\n");
        exit(0);
    }

    char* filename = (char*)calloc(MAX_FILENAME_LEN, sizeof(*filename));
    assert(filename);
    strcpy(filename, argv[1]);

    FILE* commands_file = fopen(filename, "r");
    assert(commands_file);

    double* commands_buffer = (double*)calloc(MAX_STACK_ASM_STACK_BUFFER_SIZE, sizeof(*commands_buffer));
    assert(commands_buffer);
    double* const adress_of_commands_buffer = commands_buffer;

    //malloc because I will initialise all members with -1
    double* array_of_marks = malloc(NUM_OF_MARKS * sizeof(*array_of_marks));
    assert(array_of_marks);
    memset(array_of_marks, -1.0, NUM_OF_MARKS*sizeof(array_of_marks));
    fill_array_of_marks(array_of_marks, commands_file);

    write_commands_to_buffer(commands_buffer,commands_file, array_of_marks);
    commands_buffer = adress_of_commands_buffer;

    fclose(commands_file);
    free(array_of_marks);
    array_of_marks = NULL;

    commands_file = fopen(bin_file_name(filename), "wb");
    assert(commands_file);

    free(filename);
    filename = NULL;

    write_commands_to_file(commands_buffer, commands_file);

    fclose(commands_file);
    commands_file = NULL;
    free(commands_buffer);
    commands_buffer = NULL;
    return 0;
}

/**
 \brief Gets all the commands from file and puts them into buffer (converting from string commands to
    code commands)

 @param commands_buffer Buffer that will contain commands from file
 @param commands_file File from which function will get commands
 @return 0 always
*/
int write_commands_to_buffer(double* commands_buffer, FILE* commands_file,
     double* array_of_marks)
{
    char* cmd = (char*)calloc(MAX_STRING_LENGTH, sizeof(cmd));
    assert(cmd);

    while (!feof(commands_file))
    {
        if(fscanf(commands_file, "%s", cmd) <= 0)
        {
            break;
        }
        if (cmd[0] == ':')
        {
            continue;
        }
        #define DEF_CMD(cmd_num, cmd_code, argc, code) if ((int)get_code_by_cmd_name\
                                                        (cmd, array_of_marks) == cmd_num) \
        {\
            *commands_buffer = cmd_num;\
            commands_buffer++;\
            for (int i = 0; i < argc; i++)\
            {\
                fscanf(commands_file, "%s", cmd);\
                double command_num = get_code_by_cmd_name(cmd, array_of_marks);\
                *commands_buffer = command_num;\
                commands_buffer++;\
            }\
            continue;\
        }
        #include "../Stack_cpu_cmds/cmds.h"
        #undef DEF_CMD
    }
    *commands_buffer = END_OF_BUFFER_NUM;
    commands_buffer++;

    free(cmd);
    cmd = NULL;
    return 0;
}

/**
 \brief Gets all the commands from buffer and puts them into file

 @param commands_buffer Buffer from which function will get commands
 @param commands_file File that will contain commands
 @return 0 always
*/
int write_commands_to_file(double* commands_buffer, FILE* commands_file)
{
    double* header_buffer = (double*)calloc(SIZE_OF_HEADER, sizeof(*header_buffer));
    assert(header_buffer);
    header_buffer[0] = (double)'R';
    header_buffer[1] = (double)'K';
    header_buffer[2] = (double)0;
    header_buffer[3] = (double)0;

    fwrite(header_buffer, sizeof(*header_buffer), ONE_ELEMENT*4, commands_file);
    free(header_buffer);
    header_buffer = NULL;

    for (;*commands_buffer != END_OF_BUFFER_NUM;commands_buffer++)
    {
        fwrite(commands_buffer, sizeof(*commands_buffer), ONE_ELEMENT, commands_file);
    }
    return 0;
}

/**
 \brief This function return code of command

 @param cmd String that contains command
 @return XXX_CODE Code of command
*/
double get_code_by_cmd_name(char* cmd, double* array_of_marks)
{
    if (cmd[0] == ':')
    {
        return array_of_marks[cmd[1] - '0'];
    }
    #define DEF_CMD(cmd_num, cmd_code, argc, code) else if ( strcmp(cmd, #cmd_code) == 0)\
    {\
        return cmd_num;\
    }
    #include "../Stack_cpu_cmds/cmds.h"
    #undef DEF_CMD
    return atof(cmd);//if such command doesn't exist, this is a number argv for some other command
}

int fill_array_of_marks(double* array_of_marks, FILE* commands_file)
{
    char* temp_string = (char*)calloc(MAX_STRING_LENGTH, sizeof(*temp_string));
    assert(temp_string);

    int num_of_mark=WRONG_NUM;
    int prev_is_translated = TRUE;
    int prev_is_jmp = FALSE;

    for (long i = 0; !feof(commands_file); i++)
    {
        if (prev_is_translated)
            if(fscanf(commands_file, "%s", temp_string) <= 0)
                break;
        prev_is_translated = TRUE;

        if(prev_is_jmp == FALSE && temp_string[0] == ':')
        {
            num_of_mark = temp_string[1] - '0';
            array_of_marks[num_of_mark] = i;
            i--; //because it'll be i++
        }
        else
        {
            int cmd_code = get_code_by_cmd_name(temp_string, array_of_marks);
            if (cmd_code >= JMP_NUM && cmd_code <= CALL_NUM)
            {
                prev_is_jmp = TRUE;
            }
            else
            {
                prev_is_jmp = FALSE;
            }
        }
    }

    free(temp_string);
    temp_string = NULL;
    fseek(commands_file, 0, SEEK_SET);
    return 0;
}

char* bin_file_name(char* cmds_file_name)
{
    char* rtr_val = cmds_file_name;
    long length = strlen(cmds_file_name);
    //changing ".txt" to ".bin"
    rtr_val[length-3] = 'b';
    rtr_val[length-2] = 'i';
    rtr_val[length-1] = 'n';
    return rtr_val;
}
