#include <stdio.h>
#include <assert.h>
#include <string.h>

#define NOT_A_NOTE 9999

static int get_note_idx( const char *note)
{
   int rval;
   const int xlate[7] = { 9, 11, 0, 2, 4, 5, 7 };

   if( *note >= 'A' && *note <= 'G')
      rval = xlate[*note - 'A'];
   else if( *note >= 'a' && *note <= 'g')
      rval = xlate[*note - 'a'] + 12;
   else
      rval = NOT_A_NOTE;

   if( rval != NOT_A_NOTE)
      {
      if( note[1] == ',')
         rval -= 12;
      if( note[1] == '\'')
         rval += 12;
      }
   return( rval);
}

static int get_notes( const char *buff, char *part1, char *part2)
{
   int i, j, note1 = get_note_idx( buff), note2 = NOT_A_NOTE;

   if( note1 == NOT_A_NOTE)
      return( 0);
   i = 1;
   while( buff[i] != ']' && buff[i] &&
                       (note2 = get_note_idx( buff + i)) == NOT_A_NOTE)
      i++;
   if( buff[i] == ']' || !buff[i])
      return( 0);
   memcpy( part1, buff, i);
   part1[i] = '\0';
   for( j = i; buff[j] && buff[j] != ']'; j++)
      ;
   if( !buff[j])        /* no closing ] */
      return( 0);
   memcpy( part2, buff + i, j - i);
   part2[j - i] = '\0';
   if( note1 > note2)         /* notes are in wrong order */
      {
      char tstr[40];

      strcpy( tstr, part1);
      strcpy( part1, part2);
      strcpy( part2, tstr);
      }
   return( j);
}

int main( const int argc, const char **argv)
{
   FILE *ifile = fopen( argv[1], "rb");
   int line_no = 0, i;
   char buff[400];

   assert( ifile);
   while( fgets( buff, sizeof( buff), ifile))
      {
      line_no++;
      for( i = 0; buff[i]; i++)
         if( buff[i] != '[')
            putchar( buff[i]);
         else
            {
            char part1[40], part2[40];
            int scanned = get_notes( buff + i + 1, part1, part2);

            if( !scanned)
               {
               printf( "\nFAILED to get notes\n");
               return( -1);
               }
            else
               i += scanned + 1;
            printf( "%s", (argc == 2 ? part1 : part2));
            }
      }
   fclose( ifile);
   return( 0);
}
