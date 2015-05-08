#include <stdio.h> 
#include <stdlib.h> 
#include "hash.h"

static FILE *open_file ( char *file, char *mode )
{
    FILE *fp = fopen ( file, mode );

    if ( fp == NULL ) {
        perror ( "Unable to open file" );
        exit ( EXIT_FAILURE );
    }

    return fp;
}

int main ( int argc, char *argv[] )
{
    int n;
    int ch;
    FILE *in;
    FILE *out;
    size_t BUFFSIZE = 1024 * 1024;
    unsigned char buf[BUFFSIZE];

    if ( argc != 3 ) {
        fprintf ( stderr, "Usage: %s <readfile1> <writefile2>\n", argv[0] );
        exit ( EXIT_FAILURE );
    }

    in = open_file ( argv[1], "r" );
    out = open_file ( argv[2], "w" );

    // Apparently getc is painfully slow, much faster to fread
    // into a buffer and then loop the bufer!  The current code
    // is equally fast to cp or cat
    // Should probably check performance after adding calls to
    // feof and ferror
    /*
    while ( ( ch = getc ( in ) ) != EOF )
        putc ( ch, out );
    */
    int i;
    int field_count = 1;
    while ((n = fread(buf, 1, BUFFSIZE, in)) > 0) { 
        if( ferror(in) ) return EXIT_FAILURE;
        for( i = 0; i < n; i++ ){
            if( ',' == buf[i] ) {
                buf[i] = '|';
                field_count++;
            } else if( '\n' == buf[i] ) {
                fprintf(stderr, "Number fields %d\n", field_count);
                field_count = 1;
            }
        }
        fwrite(buf, 1, n, out);
    }

    fclose ( in );
    fclose ( out );

    return EXIT_SUCCESS;
}


