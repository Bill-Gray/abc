#include <stdio.h>
#include <stdlib.h>

/* Outputs 2560 measures of pseudo-random music in ABC format,  following
the "brown noise" (1/f) method described by Martin Gardner.  He suggested
generating numbers in that distribution using three dice:  on roll N,
take the three low bits from N ^ (N-1) to determine which dice are re-rolled.
Thus,  one die is cast every time;  one every other time;  the last,  every
fourth time.  Sum them to get a number from 3 to 18 (below,  we use C
dice rather than FORTRAN dice,  so the sum can be 0 to 15;  seven dice are
rolled,  but we're just using the first three.)

   The resulting sequence of notes "looks" a bit like that of real music,
with many small changes and occasional larger changes;  at a quick glance,
you'd think it was "real" sheet music.  It doesn't sound especially musical,
however.  To this,  I added a choice of nine possible rhythms per bar.

   The result can be run through 'abcm2ps' to generate sheet music,  and/or
through 'abc2midi' to generate a somewhat bizarre-sounding MIDI file.

   As a long-time "ear" musician,  I found this helpful in learning to read
music.  My tendency in playing actual music is to anticipate by ear,
sometimes incorrectly.  Attempting to anticipate pseudo-random music is
fruitless;  it forces me to actually pay attention to what's written rather
than to what I'm expecting to hear.       */

#define N_DICE 7
#define N_RHYTHMS 9

const char *notes[] = {
         "G,", "A,", "B,",
         "C", "D", "E", "F", "G", "A", "B",
         "c", "d", "e", "f", "g", "a", "b" };

const char *rhythms[N_RHYTHMS] = {
         "*2 *2", "*2 **", "** *2", "*3 *", "* *3",    /* 5 */
         "(3*** *2", "** (3***", "**/*/ *2", "*/*/* *2" };

int main( const int argc, const char **argv)
{
   int i, counter = 0, quarter;
   unsigned dice[N_DICE];

   printf( "X:1\n");
   printf( "T: Semi-Random\n");
   printf( "C: Randomness\n");
   printf( "M: 4/4\n");
   printf( "K: G\n");
   printf( "L: 1/8\n");
   for( i = 0; i < N_DICE; i++)
      dice[i] = 0;
   for( quarter = 0; quarter < 2560; quarter++)
      {
      const char *rhythm = rhythms[rand( ) % N_RHYTHMS];

      while( *rhythm)
         {
         if( *rhythm != '*')
            printf( "%c", *rhythm);
         else
            {
            const int z = counter ^ (counter - 1);
            int note;

            for( i = 0; i < N_DICE; i++)
               if( (z >> i) & 1)
                  dice[i] = rand( ) % 6;
            note = dice[0] + dice[1] + dice[2];
            printf( "%s", notes[note]);
            counter++;
            }
         rhythm++;
         }
      if( quarter & 1)
         printf( " |");
      else
         printf( " ");
      if( (quarter & 7) == 7)
         printf( "\n");
      }
   return( 0);
}
