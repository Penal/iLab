/**
 Stack assembler (commands version 1.0)
 Zavodskikh Roman 412 group of MIPT
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Stack_asm.h"
#include "../Debug/main.c"

int main()
{
    FILE* commands_file = fopen("commands.txt", "r");
    assert(commands_file);
    double* commands_buffer = (double*)calloc(MAX_STACK_ASM_STACK_BUFFER_SIZE, sizeof(*commands_buffer));
    assert(commands_buffer);
    double* const adress_of_commands_buffer = commands_buffer;
    //malloc because I will initialise all members with -1
    double* array_of_marks = malloc(NUM_OF_MARKS * sizeof(*array_of_marks));
    assert(array_of_marks);
    for (int i = 0; i < NUM_OF_MARKS; i++)
    {
        array_of_marks[i] = -1;
    }
    fill_array_of_marks(array_of_marks, commands_file);
    write_commands_to_buffer(commands_buffer,commands_file, array_of_marks);
    commands_buffer = adress_of_commands_buffer;
    fclose(commands_file);
    free(array_of_marks);
    array_of_marks = NULL;
    commands_file = fopen("commands_num.txt", "wb");
    assert(commands_file);
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
    int prev_cmd_is_cpyed = TRUE;
    double cur_cmd_code = WRONG_NUM;
    char* cmd = (char*)calloc(MAX_STRING_LENGTH, sizeof(cmd));
    assert(cmd);
    char* Register = (char*) calloc(MAX_STRING_LENGTH, sizeof(*Register));
    assert(Register);
    while (!feof(commands_file) || !prev_cmd_is_cpyed)
    {
        if (prev_cmd_is_cpyed)
        {
            if(fscanf(commands_file, "%s", cmd) <= 0)
            {
                break;
            }
        }
        prev_cmd_is_cpyed = TRUE;
        cur_cmd_code = get_code_by_cmd_name(cmd);
        if (cur_cmd_code == PUSH_CODE)
        {
            double number = WRONG_NUM;
            if(fscanf(commands_file, "%lg", &number) > 0)
            {
                *commands_buffer = cur_cmd_code;
                commands_buffer++;
                *commands_buffer = number;
                commands_buffer++;
            }
            else
            {
                fscanf(commands_file, "%s", Register);
                strcat(cmd, Register);
                *commands_buffer = get_code_by_cmd_name(cmd);
                commands_buffer++;
            }
        }
        else if (cur_cmd_code == POP_CODE)
        {
            if(fscanf(commands_file, "%s", Register) > 0 &&
                (strcmp(Register, "A") == 0 ||
                strcmp(Register, "B") == 0 ||
                strcmp(Register, "C") == 0 ||
                strcmp(Register, "D") == 0 ||
                strcmp(Register, "X") == 0
                ))
            {
                strcat(cmd, Register);
                *commands_buffer = get_code_by_cmd_name(cmd);
                commands_buffer++;
            }
            else
            {
                *commands_buffer = get_code_by_cmd_name(cmd);
                commands_buffer++;
                strcpy(cmd, Register);
                prev_cmd_is_cpyed = FALSE;
            }
        }
        else if (cur_cmd_code == JMP_CODE ||
            cur_cmd_code == JA_CODE ||
            cur_cmd_code == JAE_CODE ||
            cur_cmd_code == JB_CODE ||
            cur_cmd_code == JBE_CODE ||
            cur_cmd_code == JE_CODE ||
            cur_cmd_code == JNE_CODE ||
            cur_cmd_code == CALL_CODE
            )
        {
            *commands_buffer = cur_cmd_code;
            commands_buffer++;
            fscanf(commands_file, "%s", cmd);
            if (cmd[0] == ':')
            {
                *commands_buffer = array_of_marks[cmd[1] - '0'];
            }
            else
            {
                *commands_buffer = atof(cmd);
            }
            commands_buffer++;
        }
        else
        {
            *commands_buffer = cur_cmd_code;
            commands_buffer++;
        }
    }
    free(cmd);
    cmd = NULL;
    free(Register);
    Register = NULL;
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
    int cur_is_arg = TRUE;
    for (;*commands_buffer != END_CODE || !cur_is_arg;commands_buffer++)
    {
        if (*commands_buffer != IGNORE_COMMAND)
        {
            fwrite(commands_buffer, sizeof(*commands_buffer), ONE_ELEMENT, commands_file);
        }
        if ((*commands_buffer == PUSH_CODE ||
            *commands_buffer == JMP_CODE ||
            *commands_buffer == JA_CODE ||
            *commands_buffer == JAE_CODE ||
            *commands_buffer == JB_CODE ||
            *commands_buffer == JBE_CODE ||
            *commands_buffer == JE_CODE ||
            *commands_buffer == JNE_CODE ||
            *commands_buffer == CALL_CODE) &&
            cur_is_arg)
        {
            cur_is_arg = FALSE;
            continue;
        }
        cur_is_arg = TRUE;
    }
    //we must not forget END in the end
    fwrite(commands_buffer, sizeof(*commands_buffer), ONE_ELEMENT, commands_file);
    return 0;
}

/**
 \brief This function return code of command

 @param cmd String that contains command
 @return XXX_CODE Code of command
*/
double get_code_by_cmd_name(char* cmd)
{
    if (strcmp(cmd,"PUSH") == 0)
    {
        return PUSH_CODE;
    }
    else if (strcmp(cmd,"ADD") == 0)
    {
        return ADD_CODE;
    }
    else if (strcmp(cmd,"MUL") == 0)
    {
        return MUL_CODE;
    }
    else if (strcmp(cmd,"SUB") == 0)
    {
        return SUB_CODE;
    }
    else if (strcmp(cmd,"DIV") == 0)
    {
        return DIV_CODE;
    }
    else if (strcmp(cmd,"SIN") == 0)
    {
        return SIN_CODE;
    }
    else if (strcmp(cmd,"COS") == 0)
    {
        return COS_CODE;
    }
    else if (strcmp(cmd,"SQRT") == 0)
    {
        return SQRT_CODE;
    }
    else if (strcmp(cmd,"END") == 0)
    {
        return END_CODE;
    }
    else if (strcmp(cmd,"JMP") == 0)
    {
        return JMP_CODE;
    }
    else if (strcmp(cmd,"JA") == 0)
    {
        return JA_CODE;
    }
    else if (strcmp(cmd,"JAE") == 0)
    {
        return JAE_CODE;
    }
    else if (strcmp(cmd,"JB") == 0)
    {
        return JB_CODE;
    }
    else if (strcmp(cmd,"JBE") == 0)
    {
        return JBE_CODE;
    }
    else if (strcmp(cmd,"JE") == 0)
    {
        return JE_CODE;
    }
    else if (strcmp(cmd,"JNE") == 0)
    {
        return JNE_CODE;
    }
    else if (strcmp(cmd,"PUSHX") == 0)
    {
        return PUSHX_CODE;
    }
    else if (strcmp(cmd,"PUSHA") == 0)
    {
        return PUSHA_CODE;
    }
    else if (strcmp(cmd,"PUSHB") == 0)
    {
        return PUSHB_CODE;
    }
    else if (strcmp(cmd,"PUSHC") == 0)
    {
        return PUSHC_CODE;
    }
    else if (strcmp(cmd,"PUSHD") == 0)
    {
        return PUSHD_CODE;
    }
    else if (strcmp(cmd,"POPX") == 0)
    {
        return POPX_CODE;
    }
    else if (strcmp(cmd,"POPA") == 0)
    {
        return POPA_CODE;
    }
    else if (strcmp(cmd,"POPB") == 0)
    {
        return POPB_CODE;
    }
    else if (strcmp(cmd,"POPC") == 0)
    {
        return POPC_CODE;
    }
    else if (strcmp(cmd,"POPD") == 0)
    {
        return POPD_CODE;
    }
    else if (strcmp(cmd,"POP") == 0)
    {
        return POP_CODE;
    }
    else if (strcmp(cmd,"CALL") == 0)
    {
        return CALL_CODE;
    }
    else if (strcmp(cmd,"RET") == 0)
    {
        return RET_CODE;
    }
    else if (strcmp(cmd, "\n") == 0 || strcmp(cmd, "") == 0 ||
         cmd[0]==':')
    {
        return IGNORE_COMMAND;
    }
    return WRONG_COMMAND;
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
            fscanf(commands_file, "%s", temp_string);
        prev_is_translated = TRUE;
        if(prev_is_jmp == FALSE && temp_string[0] == ':')
        {
            num_of_mark = temp_string[1] - '0';
            array_of_marks[num_of_mark] = i;
            i--; //because it'll be i++
        }
        else
        {
            int cmd_code = get_code_by_cmd_name(temp_string);
            if (cmd_code == JMP_CODE ||
            cmd_code == JA_CODE ||
            cmd_code == JAE_CODE ||
            cmd_code == JB_CODE ||
            cmd_code == JBE_CODE ||
            cmd_code == JE_CODE ||
            cmd_code == JNE_CODE ||
            cmd_code == CALL_CODE)
            {
                prev_is_jmp = TRUE;
            }
            else
            {
                prev_is_jmp = FALSE;
            }
            if (cmd_code == POP_CODE || cmd_code == PUSH_CODE)
            {
                fscanf(commands_file, "%s", temp_string);
                if (strcmp(temp_string, "A") != 0 &&
                strcmp(temp_string, "B") != 0 &&
                strcmp(temp_string, "C") != 0 &&
                strcmp(temp_string, "D") != 0 &&
                strcmp(temp_string, "X") != 0)
                {
                    prev_is_translated = FALSE;
                }
            }
        }
    }
    free(temp_string);
    temp_string = NULL;
    fseek(commands_file, 0, SEEK_SET);
    return 0;
}
