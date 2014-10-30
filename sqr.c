#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ORDER 2

struct Roots
{
    double r[ORDER];
    int infinity;  //Used 'int' because there's no 'bool' in C, 0 is false, 1 is true
    int no_roots;
    int accurate;
};

struct Trinomal
{
    double a;
    double b;
    double c;
};

void setCoefficients(struct Trinomal* tr, double a, double b, double c)
{
    tr->a = a;
    tr->b = b;
    tr->c = c;
}

struct Roots getRoots(struct Trinomal tr)
{
    struct Roots result;
    double d = tr.b*tr.b - 4*tr.a*tr.c;
    if (tr.a != 0)
    {
        if (d > 0)
        {
            double x1, x2;
            x1 = (-tr.b - sqrt(d)) / (2*tr.a);
            x2 = (-tr.b + sqrt(d)) / (2*tr.a);
            result.r[0] = x1;
            result.r[1] = x2;
            result.no_roots=result.infinity = 0;
        }
        else if (d == 0)
        {
            double x = -tr.b / (2*tr.a);
            result.r[0] = result.r[1] = x;
            result.no_roots=result.infinity = 0;
        }
        else
        {
            result.no_roots = 1;
            result.infinity = 0;
        }
        if (result.r[0]*result.r[1] !=
             tr.c/tr.a || result.r[0]+result.r[1] != -tr.b/tr.a)
        {
            result.accurate = 0;
        }
        else
        {
            result.accurate = 1;
        }
    }
    else
    {
        if (tr.b == 0)
        {
            if (tr.c == 0)
            {
                result.no_roots = 0;
                result.infinity = 1;
            }
            else
            {
                result.no_roots = 1;
                result.infinity = 0;
            }
        }
        else
        {
            double x = -tr.c/tr.b;
            result.r[0] = result.r[1] = x;
            result.no_roots=result.infinity = 0;
        }
        result.accurate = 1;
    }
    return result;
}

int main(void)
{
    struct Trinomal equ;
    double a = 0,b = 0, c = 0;
    scanf ("%lg %lg %lg", &a, &b, &c);
    setCoefficients(&equ , a , b , c);
    struct Roots roots = getRoots(equ);
    if (roots.infinity)
	{
		printf ("X is in R\n");
	}
	else if (roots.no_roots)
	{
		printf ("There\'re no roots\n");
	}
	else if (roots.r[0] == roots.r[1])
	{
		printf ("x = %lg\n", roots.r[0]);
	}
	else
	{
		printf ("x1 = %lg, x2 = %lg\n", roots.r[0], roots.r[1]);
	}
	if (roots.accurate == 0 && roots.no_roots == 0 && roots.infinity == 0)
	{
        printf("Unfortunately, these roots are not absolutely accurate. This is caused by the imperfe"
        "ction of computer architecture. We\'re sorry! Please use another method to solve this"
        " equation.\n");
	}
    return 0;
}
