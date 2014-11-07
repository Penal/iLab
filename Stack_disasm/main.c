#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Stack_disasm.h"

int main()
{
    FILE* commands_file = fopen("commands_num.txt", "rb");
    assert(commands_file);
    double* commands_buffer = (double*)calloc(MAX_STACK_ASM_CMDS_BUFFER_SIZE,
        sizeof(*commands_buffer));
    assert(commands_buffer);
    double* const adress_of_commands_buffer = commands_buffer;
    write_commands_to_buffer(commands_buffer,commands_file);
    commands_buffer = adress_of_commands_buffer;
    fclose(commands_file);
    commands_file = fopen("commands.txt", "w");
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
    file_length -= SIZE_OF_HEADER*sizeof(*commands_buffer); //skipping the header
    fseek(commands_file, SIZE_OF_HEADER*sizeof(*commands_buffer), SEEK_SET);
    fread(commands_buffer, sizeof(*commands_buffer), file_length/sizeof(*commands_buffer),
        commands_file);
    return 0;
}

int write_commands_to_file(double* commands_buffer, FILE* commands_file)
{
    while (*commands_buffer != 0)
    {
        if (*commands_buffer != IGNORE_COMMAND)
        {
            if (*commands_buffer == PUSH_CODE)
            {
                commands_buffer++;
                fprintf(commands_file, "%s %lg\n", "PUSH", *commands_buffer);
            }
            else if (*commands_buffer == JMP_CODE ||
            *commands_buffer == JA_CODE ||
            *commands_buffer == JAE_CODE ||
            *commands_buffer == JB_CODE ||
            *commands_buffer == JBE_CODE ||
            *commands_buffer == JE_CODE ||
            *commands_buffer == JNE_CODE ||
            *commands_buffer == CALL_CODE
            )
            {
                char* cmd_name = get_cmd_name_by_code(*commands_buffer);
                commands_buffer++;
                fprintf(commands_file, "%s %lg\n", cmd_name, *commands_buffer);
                free(cmd_name);
                cmd_name = NULL;
            }
            else
            {
                char* cmd_name = get_cmd_name_by_code(*commands_buffer);
                fprintf(commands_file, "%s\n", cmd_name);
                free(cmd_name);
                cmd_name = NULL;
            }
        }
        commands_buffer++;
    }
    return 0;
}

char* get_cmd_name_by_code(double cmd_code)
{
    char* rtr_val = (char*)calloc(MAX_STRING_LENGTH, sizeof(*rtr_val));
    switch ((int)cmd_code)
    {
     case PUSH_CODE: strcpy(rtr_val,"PUSH"); break;
     case ADD_CODE: strcpy(rtr_val, "ADD"); break;
     case MUL_CODE: strcpy(rtr_val, "MUL"); break;
     case SUB_CODE: strcpy(rtr_val, "SUB"); break;
     case DIV_CODE: strcpy(rtr_val, "DIV"); break;
     case SIN_CODE: strcpy(rtr_val, "SIN"); break;
     case COS_CODE: strcpy(rtr_val, "COS"); break;
     case SQRT_CODE: strcpy(rtr_val, "SQRT"); break;
     case END_CODE: strcpy(rtr_val, "END"); break;
     case JMP_CODE: strcpy(rtr_val, "JMP"); break;
     case JA_CODE: strcpy(rtr_val, "JA"); break;
     case JAE_CODE: strcpy(rtr_val, "JAE"); break;
     case JB_CODE: strcpy(rtr_val, "JB"); break;
     case JBE_CODE: strcpy(rtr_val, "JBE"); break;
     case JE_CODE: strcpy(rtr_val, "JE"); break;
     case JNE_CODE: strcpy(rtr_val, "JNE"); break;
     case POP_CODE: strcpy(rtr_val, "POP"); break;
     case PUSHX_CODE: strcpy(rtr_val, "PUSH X"); break;
     case PUSHA_CODE: strcpy(rtr_val, "PUSH A"); break;
     case PUSHB_CODE: strcpy(rtr_val, "PUSH B"); break;
     case PUSHC_CODE: strcpy(rtr_val, "PUSH C"); break;
     case PUSHD_CODE: strcpy(rtr_val, "PUSH D"); break;
     case POPX_CODE: strcpy(rtr_val, "POP X"); break;
     case POPA_CODE: strcpy(rtr_val, "POP A"); break;
     case POPB_CODE: strcpy(rtr_val, "POP B"); break;
     case POPC_CODE: strcpy(rtr_val, "POP C"); break;
     case POPD_CODE: strcpy(rtr_val, "POP D"); break;
     case CALL_CODE: strcpy(rtr_val, "CALL"); break;
     case RET_CODE: strcpy(rtr_val, "RET"); break;
     default: break;
    }
    return rtr_val;
}
