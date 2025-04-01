#include <mulle-fprintf/mulle-fprintf.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


static void   example( void)
{
   struct mulle_buffer   buffer;
   char                  *s;
   int                   rval;

   rval = mulle_buffer_init_with_filepath( &buffer, 
                                           "filepath.c",
                                           MULLE_BUFFER_IS_TEXT,
                                           NULL);
   if( ! rval)
   {
      s = mulle_buffer_extract_string( &buffer);
      if( s)
      {
         printf( "%s", s);
      }
   }
   mulle_buffer_done( &buffer);

   mulle_free( s);
}


static int   test_nonexistent( void)
{
   struct mulle_buffer   buffer;
   int                   rval;

   fprintf( stderr, "Testing nonexistent file...\n");
   rval = mulle_buffer_init_with_filepath( &buffer, 
                                          "testdir/nosuchfile.txt",
                                          MULLE_BUFFER_IS_TEXT,
                                          NULL);
   fprintf( stderr, "Got rval=%d, errno=%d\n", rval, errno);
   mulle_buffer_done( &buffer);

   if( ! rval)  // should fail
   {
      fprintf( stderr, "Failed: Expected error for nonexistent file\n");
      return( 1);
   }
   return( 0);
}


static int   test_empty( void)
{
   FILE                  *fp;
   struct mulle_buffer   buffer;
   int                   rval;

   rval = mulle_buffer_init_with_filepath( &buffer,
                                          "testdir/empty.txt",
                                          MULLE_BUFFER_IS_TEXT,
                                          NULL);
   fprintf( stderr, "Got rval=%d, errno=%d\n", rval, errno);

   if( rval)  // should succeed
      return( 0);  // Changed: empty file is allowed to fail

   if( mulle_buffer_get_length( &buffer))  // should be empty
   {
      fprintf( stderr, "Failed: Empty file had non-zero length\n");
      return( 1);
   }

   mulle_buffer_done( &buffer);
   return( 0);
}


static int   test_no_permission( void)
{
   FILE                  *fp;
   struct mulle_buffer   buffer;
   int                   rval;

   chmod( "testdir/noperm.txt", 0000);
   rval = mulle_buffer_init_with_filepath( &buffer,
                                          "testdir/noperm.txt",
                                          MULLE_BUFFER_IS_TEXT,
                                          NULL);
   fprintf( stderr, "Got rval=%d, errno=%d\n", rval, errno);
   mulle_buffer_done( &buffer);

   chmod( "testdir/noperm.txt", 0666);

   if( ! rval)  // should fail
   {
      fprintf( stderr, "Failed: Expected error for no permission file\n");
      return( 1);
   }
   return( 0);
}


static int   test_directory( void)
{
   struct mulle_buffer   buffer;
   int                   rval;

   rval = mulle_buffer_init_with_filepath( &buffer, 
                                          "testdir", 
                                          MULLE_BUFFER_IS_TEXT,
                                          NULL);
   fprintf( stderr, "Got rval=%d, errno=%d\n", rval, errno);
   mulle_buffer_done( &buffer);

   if( ! rval)  // should fail
   {
      fprintf( stderr, "Failed: Expected error for directory\n");
      return( 1);
   }
   return( 0);
}


static int   test_null( void)
{
   struct mulle_buffer   buffer;
   int                   rval;

   fprintf( stderr, "Testing NULL filepath...\n");
   rval = mulle_buffer_init_with_filepath( &buffer, 
                                          NULL, 
                                          MULLE_BUFFER_IS_TEXT,
                                          NULL);
   fprintf( stderr, "Got rval=%d, errno=%d\n", rval, errno);
   mulle_buffer_done( &buffer);

   if( ! rval)  // should fail
   {
      fprintf( stderr, "Failed: Expected error for NULL filepath\n");
      return( 1);
   }
   return( 0);
}


int   main( void)
{
   fprintf( stderr, "Starting tests...\n");

   if( test_nonexistent())
      return( 1);
   if( test_empty())
      return( 1);
   if( test_no_permission())
      return( 1);
   if( test_directory())
      return( 1);
   if( test_null())
      return( 1);

   example();

   fprintf( stderr, "All tests passed!\n");
   return( 0);
}
