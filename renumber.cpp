#include <stdio.h>

/* Code to reset the numbering on an ABC file.  At present,  it
simply numbers tunes consecutively with odd numbers,  allowing
some 'wiggle room' if intermediate tunes are added later. */

void main( int argc, char **argv)
{
   FILE *ifile = fopen( argv[1], "rb");
   char buff[300];
   int count = 1;

   if( ifile)
      while( fgets( buff, sizeof( buff), ifile))
         {
         if( *buff == 'X' && buff[1] == ':')
            {
            sprintf( buff + 2, "%d\n", count);
            count += 2;
            }
         printf( "%s", buff);
         }
}
