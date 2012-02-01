#include <stdio.h>
#include <stdlib.h>

/*
 * These are nested deeply enough that the default stack size is too small:
 * ((((( )))))
 */
int
main ( int argc, char **argv )
{
    printf ( "This file is perfectly balanced\n" );
    exit ( EXIT_SUCCESS );
}
