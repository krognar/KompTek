#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#ifndef INIT_STACKSIZE
#define INIT_STACKSIZE 2
#endif


/*
 * Define a structure for tracking positions in text in
 * terms of line number and position on line
 */
typedef struct {
    int32_t line, count;
} position_t;

/* Pointer to the array we will use as a stack */
position_t *parens;

/* Controls the return value at program termination */
bool input_ok = true;

int32_t
    size = INIT_STACKSIZE,
    top = -1;


void
push ( position_t p )
{
    top++;
    if(top >= size)
        parens = (position_t *) realloc( parens, (size += 3) * sizeof(position_t));
    parens[top] = p;
}


bool
pop ( position_t *p, position_t now)
{
    if(top < 0) {
    fprintf(stderr, "Excess ')' at line '%d' char '%d'\n", now.line, now.count);
    return false;
    }
    (*p) = parens[top--];
    return true;
}


bool
check ( void )
{
    if(top < 0)
        return true;
    int i;
    for(i = 0; i<=top; i++)
        fprintf(stderr, "Excess '(' at line '%d' char '%d'\n", parens[i].line, parens[i].count);
    return false;
}


int
main ( int argc, char **argv )
{
    int32_t c = getchar();

    position_t
        now = { .line = 1, .count = 1 },   /* Track where we are in the input */
        balance;                           /* Space for the matching position
                                               when parentheses are closed */

    parens = (position_t *) malloc ( size * sizeof(position_t) );
    while ( ! feof(stdin) )
    {
        switch(c)
        {
            case '(':
                   push(now);
                   break;
            case ')':
                    input_ok = pop(&balance, now);
                    break;
            case '\n':
                    now.line++;
                    now.count = 0;
                    break;
        }
        now.count += 1;
        c = getchar();
    }
    check();
    printf ( "Total of %d lines\n", now.line-1 );
    free ( parens );
    exit ( (input_ok) ? EXIT_SUCCESS : EXIT_FAILURE );
}
