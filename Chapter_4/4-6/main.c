#include <stdio.h>
#include <stdlib.h>  /* for atof() */
#include <stdbool.h>
#include <math.h>
#include "calc.h"

#define MAXOP    100 /* max size of operand or operator */
#define tpush(x)    push(top_elem = (x))  /* make sure top_elem always right */

/* Exercise 4-6. Add commands for handing variables. (It's easy to provide
 * twenty-six vriables with single-letter names.) Add a variable for the most
 * recently printed value. */

void helpinfo();

/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2, top_elem;
    double x, y, z;    /* declare variables x, y, z */
    char s[MAXOP];
    bool assign, arithmetic;

    assign = arithmetic = false;
    x = y = z = 0.0;
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                tpush(atof(s));
                break;

            case '+':
                tpush(pop() + pop());
                break;

            case '*':
                tpush(pop() * pop());
                break;

            case '-':
                op2 = pop();
                tpush(pop() - op2);
                break;

            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    tpush(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;

            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    tpush((int)pop() % (int)op2);
                else
                    printf("error: zero divisor\n");
                break;

            case '\n':
                printf("\t%.8g\n", pop());
                break;

            case 'h':    /* show help info */
                helpinfo();
                break;

            case 'p':    /* print top element of the stack */
                printf("\n\ttop element of the stack: %.8g\n", top_elem);
                break;

            case 'd':    /* duplicate top element */
                tpush(top_elem);
                printf("\n\ttop element has been duplicated\n");
                break;

            case 's':    /* swap the top two elements */
                {
                    double elem1, elem2;
                    elem1 = pop();
                    elem2 = pop();
                    tpush(elem1);
                    tpush(elem2);
                    printf("\n\tthe top two elements have been swapped\n");
                }
                break;

            case 'i':    /* sin() */
                tpush(sin(pop()));
                break;

            case 'c':    /* cos() */
                tpush(cos(pop()));
                break;

            case 'e':    /* exp() */
                tpush(exp(pop()));
                break;

            case 'w':    /* pow() */
                {
                    double x, y;
                    y = pop();
                    x = pop();
                    if (x == 0 && y < 0 ||
                            x < 0 && y-(int)y != 0)    /* verify if y is an integer */
                        printf("error:  pow(x,y) error\n");
                    tpush(pow(x, y));
                }
                break;

                /* TODO: complete variable */
            case 'v':    /* show variables */
                printf("\n\nvariables:\n");
                printf("\tx:  %g\n", x);
                printf("\ty:  %g\n", y);
                printf("\tz:  %g\n", z);
                break;

            case '=':    /* for assignment of variables */
                assign = true;
                break;

            case '&':    /* for arithmetic operation of variables */
                arithmetic = true;
                break;

            case 'x':    /* variable x */
                if (assign) {
                    x = pop();
                    printf("\n\tx:  %g\n", x);
                    assign = false;
                } else if (arithmetic) {
                    tpush(x);
                    arithmetic = false;
                }
                break;

            case 'y':    /* variable y */
                if (assign) {
                    y = pop();
                    printf("\n\ty:  %g\n", y);
                    assign = false;
                } else if (arithmetic) {
                    tpush(y);
                    arithmetic = false;
                }
                break;

            case 'z':    /* variable z */
                if (assign) {
                    z = pop();
                    printf("\n\tz:  %g\n", z);
                    assign = false;
                } else if (arithmetic) {
                    tpush(z);
                    arithmetic = false;
                }
                break;

            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

/* helpinfo:  print help information */
void helpinfo()
{
    printf("\n\n<============== Reverse Polish Calculator ============>\n\n");
    printf("h:  print help infomation\n");
    printf("p:  print top element of the stack\n");
    printf("d:  duplicate top element\n");
    printf("s:  swap the top two elements\n");
    printf("i:  sin()\n");
    printf("c:  cos()\n");
    printf("e:  exp()\n");
    printf("w:  pow()\n");
    printf("v:  show variables\n");
    printf("\n");
}