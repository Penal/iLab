//*Please don't divide or reorder ALL this commands
#include <limits.h>

#define POP_ stack_pop(cpu_p->cpu_data);
#define POPU double upper = stack_pop(cpu_p->cpu_data);
#define POPL double lower = stack_pop(cpu_p->cpu_data);
#define POP_CALL i = stack_pop(cpu_p->call_stack) - 1;


#define PUSH_(arg) stack_push(cpu_p->cpu_data, arg)
#define PUSH_CALL(arg) stack_push(cpu_p->call_stack, arg)

#define JMP_ i = cpu_p->commands_to_execute[i]-1
#define JMP_IF(cond) if (upper cond lower) {i = cpu_p->commands_to_execute[i] - 1;}

#define ER(msg) CPU_ERR(cpu_p, msg)
#define CUR_CMD cpu_p->commands_to_execute[i]

DEF_CMD(1, END, 0, {break;})
DEF_CMD(2, ADD, 0,
    {
        POPU POPL PUSH_(lower+upper);
    }
    )
DEF_CMD(3, MUL, 0,
    {
        POPU POPL PUSH_(lower*upper);
    }
    )
DEF_CMD(4, SUB, 0,
    {
        POPU POPL PUSH_(lower-upper);
    }
    )
DEF_CMD(5, DIV, 0,
    {
        POPU POPL
        if (upper == 0)
        {
            ER("Division by zero");
        }
        PUSH_(lower/upper);
    }
)
DEF_CMD(6, SIN, 0,
    {
        POPU PUSH_(sin(upper));
    }
)
DEF_CMD(7, COS, 0,
    {
        POPU PUSH_(cos(upper));
    }
    )
DEF_CMD(8, SQRT, 0,
    {
        POPU
        if (upper < 0)
        {
            ER("Taking root of negative number");
        }
        PUSH_(sqrt(upper));
    }
)
DEF_CMD(9, PUSH, 1,
    {
        i++;
        PUSH_(CUR_CMD);
    }
)
DEF_CMD(10, JMP, 1,
    {
        i++;
        JMP_;
        continue;
    }
)
DEF_CMD(11, JA, 1,
    {
        i++;
        POPU POPL
        JMP_IF(>)
        PUSH_(lower);
        PUSH_(upper);
        continue;
    }
    )
DEF_CMD(12, JAE, 1,
    {
        i++;
        POPU POPL
        JMP_IF(>=)
        PUSH_(lower);
        PUSH_(upper);
        continue;
    }
)
DEF_CMD(13, JB, 1,
    {
        i++;
        POPU POPL
        JMP_IF(<)
        PUSH_(lower);
        PUSH_(upper);
        continue;
    }
)
DEF_CMD(14, JBE, 1,
    {
        i++;
        POPU POPL
        JMP_IF(<=)
        PUSH_(lower);
        PUSH_(upper);
        continue;
    }
)
DEF_CMD(15, JE, 1,
    {
        i++;
        POPU POPL
        JMP_IF(==)
        PUSH_(lower);
        PUSH_(upper);
        continue;
    }
)
DEF_CMD(16, JNE, 1,
    {
        i++;
        POPU POPL
        JMP_IF(!=)
        PUSH_(lower);
        PUSH_(upper);
        continue;
    }
)
DEF_CMD(17, CALL, 1,
    {
        i++;
        PUSH_CALL(i+1);
        JMP_;
        continue;
    }
)
DEF_CMD(18, OUT, 0,
    {
        POPU
        printf("---OUT VALUE: %lg|\n", upper);
    }
)
DEF_CMD(19, IN, 0,
    {
        double temp = WRONG_NUM;
        printf("Input value to data stack: ");
        scanf("%lg", &temp);
        PUSH_(temp);
    }
)
DEF_CMD(20, POP, 0,
    {
        POP_;
    }
)
DEF_CMD(21, RET, 0,
    {
        POP_CALL;
    }
)
DEF_CMD(INT_MIN, END_OF_BUFFER, 0, {break;})
DEF_CMD(25, PUSHAX, 0,
    {
        PUSH_(cpu_p->a_reg);
    }
)
DEF_CMD(26, PUSHBX, 0,
    {
        PUSH_(cpu_p->b_reg);
    }
)
DEF_CMD(27, PUSHCX, 0,
    {
        PUSH_(cpu_p->c_reg);
    }
)
DEF_CMD(28, PUSHDX, 0,
    {
        PUSH_(cpu_p->d_reg);
    }
)
DEF_CMD(29, POPAX, 0,
    {
        POPU;
        cpu_p->a_reg = upper;
    }
)
DEF_CMD(30, POPBX, 0,
    {
        POPU;
        cpu_p->b_reg = upper;
    }
)
DEF_CMD(31, POPCX, 0,
    {
        POPU;
        cpu_p->c_reg = upper;
    }
)
DEF_CMD(32, POPDX, 0,
    {
        POPU;
        cpu_p->d_reg = upper;
    }
)


