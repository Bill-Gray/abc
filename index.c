#include <stdio.h>
#include <assert.h>
#include <string.h>

/* Code to read 'index.txt' and create a two-column PostScript
index file.  Compile with

gcc -Wall -Wextra -pedantic -o index index.c   */

int main( void)
{
   FILE *ifile = fopen( "header.ps", "rb");
   char buff[200];
   int n_lines = 0;
   const int line_freq = 100;

   assert( ifile);
   while( fgets( buff, sizeof( buff), ifile))
      printf( "%s", buff);
   fclose( ifile);

   ifile = fopen( "index.txt", "rb");
   assert( ifile);
   while( fgets( buff, sizeof( buff), ifile))
      n_lines++;
   fseek( ifile, 0L, SEEK_SET);

   n_lines = 0;
   while( fgets( buff, sizeof( buff), ifile))
      {
      if( !(n_lines % line_freq))
         {
         if( n_lines)
            printf( "showpage\n");
         printf( "%%%%Page: %d %d\n", n_lines / line_freq + 1, n_lines / line_freq + 1);
         printf( "setup\n");
         }
      if( *buff)
         {
         buff[strlen( buff) - 1] = '\0';
         buff[8] = '\0';
         printf( "(%s) (%s) z\n", buff, buff + 9);
         n_lines++;
         }
      }
   fclose( ifile);
   printf( "showpage\n");
   return( 0);
}
