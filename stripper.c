#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* Code to read in ABC files and remove chords,  bowings,  words,  etc. */

static void strip_chords( char *buff)
{
   while( *buff)
      {
      if( *buff == '"' && buff[1] >= 'A' && buff[1] <= 'G')
         {
         size_t i = 1;

         while( buff[i] && buff[i] != '"')
            i++;
         assert( buff[i] == '"');
         assert( i < 6);
         memmove( buff, buff + i + 1, strlen( buff + i));
         }
      buff++;
      }
}

static void strip_bowings( char *buff)
{
   char *tptr = buff;

   while( *tptr)
      {
      if( *tptr != 'u' && *tptr != 'v')
         *buff++ = *tptr;
      tptr++;
      }
   *buff++ = '\0';
}

static void strip_dynamics( char *buff)
{
   while( *buff)
      {
      if( *buff == '!')
         {
         size_t i = 1;

         while( buff[i] && buff[i] != '!')
            i++;
         assert( buff[i] == '!');
         assert( i < 6);
         memmove( buff, buff + i + 1, strlen( buff + i));
         }
      buff++;
      }
}

static void strip_slurs( char *buff)
{
   size_t i = 0, j = 0;

   while( buff[i])
      {
      if( buff[i] == '(' && buff[i + 1] != '3')    /* keep triplets */
         i++;
      else if( buff[i] == ')')
         i++;
      else
         buff[j++] = buff[i++];
      }
   buff[j] = '\0';
}

static void strip_words( char *buff)
{
   if( *buff == 'w' && buff[1] == ':')
      *buff = '\0';
}

int main( const int argc, const char **argv)
{
   FILE *ifile = fopen( argv[1], "rb");
   char buff[300];

   assert( ifile);
   while( fgets( buff, sizeof( buff), ifile))
      {
      if( buff[1] != ':')
         {
         strip_chords( buff);
         strip_slurs( buff);
         strip_bowings( buff);
         strip_dynamics( buff);
         }
      strip_words( buff);
      if( *buff)
         printf( "%s", buff);
      }
   fclose( ifile);
   return( 0);
}
