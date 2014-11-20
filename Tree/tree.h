#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
typedef unsigned char* T;
typedef struct Node_t
{
    T data;
    struct Node_t* lft;
    struct Node_t* rgt;
} Node_t;

enum {FALSE = 0, TRUE = 1};

enum {LEFT, RIGHT};

enum
{
    GOOD_TREE,
};
int Node_errno = GOOD_TREE;

const int ONE_ELEMENT = 1;
const int WRONG_NUM = -13;
const int MAX_STRLEN = 300;

Node_t* Node_ctor(T value, Node_t* lft, Node_t* rgt, FILE* dump_file);
int Node_dtor(Node_t* node_p, FILE* dump_file);
int Node_ok(Node_t* tree_p, FILE* dump_file);
int Node_dump(Node_t* tree_p, FILE* dump_file, int level);
int Node_insert(Node_t* node_p,Node_t* node_to_ins, int LFT_OR_RGT,FILE* dump_file);
int Node_delete(Node_t* node_p, FILE* dump_file);
int Node_fprint(Node_t* tree_p, FILE* file, FILE* dump_file);
Node_t* Node_fread(FILE* file, FILE* dump_file);
char* Node_strerror();

int Print_msg_to_dump(char* msg,FILE* dump_file);
#endif // TREE_H_INCLUDED
