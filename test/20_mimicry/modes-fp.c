#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


static void   test_file( FILE *fp)
{
   int   res1;
   long  off;

   off   = ftell( fp);
   printf( "off %ld\n", off);

   errno = 0;
   res1  = fseek( fp, -2, SEEK_CUR);
   printf( "res1 %d: %s\n", res1, strerror( errno));

   off   = ftell( fp);
   printf( "off %ld\n", off);

   errno = 0;
   res1  = fputc( 'X', fp);
   printf( "res1 %d: %s\n", res1, strerror( errno));

   off   = ftell( fp);
   printf( "off %ld\n", off);

   errno = 0;
   res1  = fseek( fp, 0, SEEK_END);
   printf( "res1 %d: %s\n", res1, strerror( errno));

   off   = ftell( fp);
   printf( "off %ld\n", off);
}


static void   test( char *mode)
{
   FILE   *fp;
   char   test_string[] = "VfL Bochum 1848";

   printf( "---------------- %s ----------------\n", mode);
   fp = fmemopen( (void *) test_string, strlen( test_string) - 4, mode);
   if( ! fp)
      abort();

   test_file( fp);

   printf( "s: \"%s\"\n", test_string);
   fclose( fp);
}


int   main( void)
{
   test( "r");
   test( "w");
   test( "a");
   test( "r+");
   test( "w+");
   test( "a+");

   return( 0);
}
