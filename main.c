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
    size_t MAPSIZE = 1024;
    map m;
    int n;
    int ch;
    FILE *in;
    FILE *out;
    size_t BUFFSIZE = 1024 * 1024;
    unsigned char buf[BUFFSIZE];

    map_init(&m, 1024);

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

    // Want to enable multichar delimiter, quote and escape sequences
    // as I think it'll be pretty valuable
    char *delimiter = "||";
    char *quote = "\"";
    char *escape = "\\";
    char *newline = "\n";

    // Character Sequence Explanations:
    // --------------------------------
    //
    //   delimiter - separates each field from another, but ignored if
    //               contained in a quoted section or if escaped
    //   quote - may only come at the beginning or end of a field and so 
    //
    //              <DELIM> <QUOTE> followed by <QUOTE> <DELIM> OR
    //              <NEWLINE> <QUOTE> followed by <QUOTE> <DELIM> OR
    //              <DELIM> <QUOTE> followed by <QUOTE> <NEWLINE> OR
    //              <NEWLINE> <QUOTE> followed by <QUOTE> <NEWLINE>
    //
    //           and the code will keep reading until it is matched unless
    //           there is a newline in strict newline mode.
    //   escape - an escape in any location will cause the following special
    //            sequence to be treated as a plain string. If the following
    //            sequence is not special, it will be treated as itself.
    //   newline - terminates a record. If it's located in a quoted section
    //             or proceeds an escape sequence, then it'll be ignored, unless
    //             strict newline is on.

    // State Machine Description:
    // --------------------------
    //
    //   0) Reading Chars 
    //      0 -> 1) Matched first byte of delimiter
    //      0 -> 2) Matched first byte of quote
    //      0 -> 3) Matched first byte of escape
    //      0 -> 4) Matched first byte of newline
    //   1) Matching Delimiter
    //      1 -> 0) Failed to match full delimiter
    //      1 -> 4) 
    //   2) 

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


