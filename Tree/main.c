/**
    Realization of tree
    Zavodskikh Roman, 412, MIPT
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"

#define DEBUG_TREE

#ifdef DEBUG_TREE
#define VALID_NODE(tree_p, msg, dump_file) \
if (!Node_ok(tree_p, dump_file))\
{\
    Print_msg_to_dump(msg, dump_file);\
    Node_dump(tree_p, dump_file, 0);\
    assert(NULL);\
}
#else
#define VALID_NODE(tree_p, msg, dump_file)
#endif // DEBUG_TREE

/**
    @brief Allocate the memory and construct the node of tree

    @param value Some value that node will contain
    @param lft Pointer to left node (or NULL)
    @param rgt Pointer to right node (or NULL)
    @param dump_file File that may contain dump info
    @return ptr_val Pointer to constructed node
*/
Node_t* Node_ctor(T value, Node_t* lft, Node_t* rgt, FILE* dump_file)
{
    assert(dump_file);

    Node_t* node_p = (Node_t*)calloc(ONE_ELEMENT, sizeof(*node_p));
    assert(node_p);

    node_p->data = value;
    node_p->lft = lft;
    node_p->rgt = rgt;

    return node_p;
}

/**
    @brief Destructs node and ALL of subnodes

    @param node_p Pointer to node
    @param dump_file File that may contain debug info
    @return 0 always
*/
int Node_dtor(Node_t* node_p, FILE* dump_file)
{
    assert(dump_file);
    VALID_NODE(node_p, "Invalid node in the beginning of Node_dtor", dump_file);

    free(node_p->data);
    node_p->data = NULL;

    if (node_p->lft)
    {
        Node_dtor(node_p->lft, dump_file);
        node_p->lft = NULL;
    }
    if (node_p->rgt)
    {
        Node_dtor(node_p->rgt, dump_file);
        node_p->rgt = NULL;
    }
    free(node_p);

    return 0;
}

/**
    @brief Tells if tree is ok and writes info to Node_errno variable

    @param tree_p Checkable tree
    @param dump_file File that may contain debug info
    @return TRUE if good, FALSE if bad
*/
int Node_ok(Node_t* tree_p, FILE* dump_file)
{
    Node_errno = GOOD_TREE;
    return TRUE;
}

/**
    @brief If DEBUG_TREE is defined prints debug info to dump file, else does nothing

    @param tree_p Pointer to node about which we want to know
    @param dump_file File that may contain debug info
    @param level Relative depth of node in tree
    @return 0 always
*/
int Node_dump(Node_t* tree_p, FILE* dump_file, int level)
{
    #ifdef DEBUG_TREE
    assert(dump_file);
    assert(tree_p);

    for(int i = 0; i < level; i++)
    {
        fprintf(dump_file, "\t");
    }

    fprintf(dump_file,"(\"%s\" [%p], lft: [%p], rgt: [%p]---->",
         tree_p->data, (void*)tree_p, (void*)tree_p->lft, (void*)tree_p->rgt);
    if(Node_ok(tree_p, dump_file))
    {
        fprintf(dump_file, "[ok]");
    }
    else
    {
        fprintf(dump_file, "%s" , Node_strerror());
    }
    fprintf(dump_file, "\n");

    if(tree_p->lft) Node_dump(tree_p->lft, dump_file, level+1);
    if(tree_p->rgt) Node_dump(tree_p->rgt, dump_file, level+1);

    fprintf(dump_file, ")\n");
    #endif // DEBUG_TREE

    return 0;
}

/**
    @brief Decodes info from Node_errno variable

    @return rtr_val String that tells about Node_errno
*/
char* Node_strerror()
{
    char* rtr_val = NULL;
    switch(Node_errno)
    {
        case GOOD_TREE:                                    rtr_val="Good tree"; break;
        default: rtr_val="SOME UNEXPECTED SITUATION. ASK DEVELOPER TO FIX IT."; break;
    }
    return rtr_val;
}

/**
    @brief Prints some message to dump file

    @param dump_file File that may contain debug info
*/
int Print_msg_to_dump(char* msg,FILE* dump_file)
{
    fprintf(dump_file, "|||---|||%s|||---|||\n", msg);
    return 0;
}

/**
    @brief Inserts node in tree

    @param node_p Pointer to node that will point to inserted node
    @param node_to_ins Pointer to node that will be inserted in tree
    @param LFT_OF_GRT LEFT or RIGHT value because of which node will be inserted in left or right
    @param dump_file File that may contain debug info
    @return 0 always
*/
int Node_insert(Node_t* node_p,Node_t* node_to_ins, int LFT_OR_RGT,FILE* dump_file)
{
    VALID_NODE(node_p, "Invalid base tree in the beginning of Node_insert", dump_file);
    VALID_NODE(node_to_ins, "Invalid tree to insert in the beginning of Node_insert", dump_file);
    assert(dump_file);

    if (LFT_OR_RGT == LEFT)
    {
        if (node_p->lft)
        {
            Print_msg_to_dump("Replaced some node(lft)", dump_file);
        }
        node_p->lft = node_to_ins;
    }
    else if (LFT_OR_RGT == RIGHT)
    {
        if (node_p->rgt)
        {
            Print_msg_to_dump("Replaced some node(rgt)", dump_file);
        }
        node_p->rgt = node_to_ins;
    }
    else
    {
        Print_msg_to_dump("ERROR: Node_insert don't right know LFT_OF_RGT", dump_file);
    }

    VALID_NODE(node_p, "Invalid tree in the end of Node_insert", dump_file);
    VALID_NODE(node_to_ins, "Invalid tree in the end of Node_insert", dump_file);
    return 0;
}

/**
    @brief Delete node and ALL of subnodes

    @param node_p Pointer to deletable node
    @param dump_file File that may contain debug info
    @return 0 always
*/
int Node_delete(Node_t* node_p, FILE* dump_file)
{
    assert(dump_file);
    VALID_NODE(node_p, "Invalid node in the beginning of Node_delete", dump_file);

    Node_dtor(node_p, dump_file);

    return 0;
}

/**
    @brief Prints node and ALL subnodes in preorder to file

    @param tree_p Pointer to node
    @param file File thah will contain nodes
    @param dump_file File that may contain debug info
    @return 0 always
*/
int Node_fprint(Node_t* tree_p, FILE* file, FILE* dump_file)
{
    VALID_NODE(tree_p, "Invalid node in the beginning of Node_fprint", dump_file);
    assert(file);

    fprintf(file,"(\"%s\"", tree_p->data);
    if (tree_p->lft)
    {
        Node_fprint(tree_p->lft, file, dump_file);
    }
    else
    {
        fprintf(file, "(0)");
    }

    if (tree_p->rgt)
    {
        Node_fprint(tree_p->rgt, file, dump_file);
    }
    else
    {
        fprintf(file, "(0)");
    }
    fprintf(file, ")");

    VALID_NODE(tree_p, "Invalid node in the end of Node_fprint", dump_file);

    return 0;
}

/**
    @brief Reads tree from file and construct it

    @param file File that will be read
    @param dump_file File that may contain debug info
    @return rtr_val Pointer to constructed tree
*/
Node_t* Node_fread(FILE* file, FILE* dump_file)
{
    assert(file);
    assert(dump_file);

    int temp = WRONG_NUM;
    if (fscanf(file, "(%i)", &temp) > 0 && temp == 0)
    {
        return NULL;
    }

    fscanf(file, "(");

    unsigned char* buffer = (unsigned char*)calloc(MAX_STRLEN, sizeof(*buffer));
    assert(buffer);
    fscanf(file, "\"%[^\"]\"", buffer);

    Node_t* return_node = Node_ctor(buffer, NULL, NULL, dump_file);

    Node_t* left_node = Node_fread(file, dump_file);
    Node_insert(return_node, left_node, LEFT, dump_file);

    Node_t* right_node = Node_fread(file, dump_file);
    Node_insert(return_node, right_node, RIGHT, dump_file);

    fscanf(file, ")");

    VALID_NODE(return_node, "Invalid node in the end of Node_fread", dump_file)
    return return_node;
}
