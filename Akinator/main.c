#include <stdio.h>
#include <stdlib.h>

#include "../Tree/main.c"
#include "akinator.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        exit(0);
    }

    FILE* dump_file = fopen("dump.txt", "w");

    FILE* akinator_file = fopen(argv[1], "r");
    assert(akinator_file);
    Node_t* akinator_dtbase = Node_fread(akinator_file, dump_file);
    fclose(akinator_file);
    akinator_file = NULL;

    akinator_play(akinator_dtbase, dump_file);

    akinator_file = fopen(argv[1], "w");
    assert(akinator_file);
    Node_fprint(akinator_dtbase, akinator_file, dump_file);
    fclose(akinator_file);
    akinator_file = NULL;

    Node_dtor(akinator_dtbase, dump_file);
    fclose(dump_file);
    dump_file = NULL;
    return 0;
}

/**
    @brief Runs Akinator game

    @param akirnator_dtbase Tree that contain Akinator database
    @param dump_file File that must contain debug info
*/
int akinator_play(Node_t* akinator_dtbase,FILE* dump_file)
{
    assert(dump_file);
    VALID_NODE(akinator_dtbase, "Invalid node in the beginning of akinator_play", dump_file);

    Node_t* const head = akinator_dtbase;

    char* reply = (char*)calloc(MAX_STRLEN, sizeof(*reply));
    int want_to_play = TRUE;
    int yes_or_no = WRONG_NUM;

    while (want_to_play)
    {
        yes_or_no = get_yes_or_no_answer("Do you want to play");
        if (yes_or_no == YES)
        {
            while( !(akinator_dtbase->lft == NULL && akinator_dtbase->rgt == NULL) )
            {
                yes_or_no = get_yes_or_no_answer((char*)akinator_dtbase->data);
                if (yes_or_no == YES)
                {
                    akinator_dtbase = akinator_dtbase->lft;
                }
                else if (yes_or_no == NO)
                {
                    akinator_dtbase = akinator_dtbase->rgt;
                }
                else
                {
                    printf("I don\'t understand you.\n");
                    continue;
                }
            }

            sprintf(reply, "This is %s?, Am I right", akinator_dtbase->data);
            yes_or_no = get_yes_or_no_answer(reply);

            while (yes_or_no != YES)
            {
                if (yes_or_no == NO)
                {
                    akinator_create_new_person(akinator_dtbase, dump_file);
                    yes_or_no = YES;
                }
                else
                {
                    yes_or_no = get_yes_or_no_answer("I didn\'t understand you");
                }
            }
            akinator_dtbase = head;
        }
        else if (yes_or_no == NO)
        {
            want_to_play = FALSE;
            break;
        }
        else
        {
            printf("I don\'t understand you.\n");
            continue;
        }
    }

    free(reply);
    reply = NULL;
    VALID_NODE(akinator_dtbase, "Invalid node in the end of akinator_play", dump_file);
    return 0;
}

/**
    @brief Ask user about something with console

    @param msg Question that function aks
    @return YES, NO or DONT_UNDERSTAND answer
*/
int get_yes_or_no_answer(char* msg)
{
    assert(msg);

    printf("%s?, ", msg);

    unsigned char* ans = (unsigned char*)calloc(MAX_SIZE_OF_ANS, sizeof(*ans));
    assert(ans);
    scanf("%s", ans);
    int rtr_val = WRONG_NUM;

    if(ans[0] == 'y' || ans[0] == 'Y')
    {
        rtr_val = YES;
    }
    else if (ans[0] == 'n' || ans[0] == 'N')
    {
        rtr_val = NO;
    }
    else
    {
        rtr_val = DONT_UNDERSTAND;
    }


    free(ans);
    ans = NULL;
    return rtr_val;
}

/**
    @brief Creates new person.

    @param akinator_dtbase Node that will be splitted
    @param dump_file File that must contain debug info
*/
int akinator_create_new_person(Node_t* akinator_dtbase, FILE* dump_file)
{
    assert(dump_file);
    VALID_NODE(akinator_dtbase, "Invalid node in the beginning of akinator_create_new_person", dump_file);

    printf("Whom did you mean?, ");
    T name = (T)calloc(MAX_STRLEN, sizeof(*name));
    assert(name);
    scanf("\n");
    scanf("%[^\n]", name);

    printf("What is in %s, but is not in %s?, ", name, akinator_dtbase->data);
    T difference = (T)calloc(MAX_STRLEN, sizeof(*difference));
    assert(difference);
    scanf("\n");
    scanf("%[^\n]", difference);

    Node_t* left_node  = Node_ctor(name, NULL, NULL, dump_file);
    Node_t* rigth_node = Node_ctor(akinator_dtbase->data, NULL, NULL, dump_file);

    akinator_dtbase->data = difference;
    Node_insert(akinator_dtbase, left_node, LEFT, dump_file);
    Node_insert(akinator_dtbase, rigth_node, RIGHT, dump_file);

    VALID_NODE(akinator_dtbase, "Invalid node in the end of akinator_create_new_person", dump_file);
    return 0;
}
