#include <stdio.h>


int  main( void)
{
   FILE  *fp;

   fp = fmemopen( NULL, 100, "w");
   if( ! fp)
   {
      perror( "fmemopen:");
      return( 1);
   }
   fclose( fp);
   return( 0);
}


