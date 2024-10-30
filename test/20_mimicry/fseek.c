#include <mulle-fprintf/mulle-fprintf.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>



static void compare_seek_tell(FILE *fp, struct mulle_buffer *buffer, const char *test_name)
{
    long pos1, pos2;
    int res1, res2;
    int errno1, errno2;
    int c1, c2;

    // Test initial position
    errno = 0;
    pos1 = ftell( fp);
    errno1 = errno;

    errno = 0;
    pos2 = mulle_buffer_ftell( buffer);
    errno2 = errno;

    printf("%s - Initial position: FILE*=%ld (errno=%d), mulle_buffer=%ld (errno=%d)\n",
           test_name, pos1, errno1, pos2, errno2);

    // Seek to position 3
    errno = 0;
    res1 = fseek( fp, 3, SEEK_SET);
    errno1 = errno;

    errno = 0;
    res2 = mulle_buffer_fseek( buffer, 3, SEEK_SET);
    errno2 = errno;

    printf("%s - Seek to 3: FILE*=%d (errno=%d), mulle_buffer=%d (errno=%d)\n",
           test_name, res1, errno1, res2, errno2);

    // Read character at position 3
    errno = 0;
    c1 = fgetc( fp);
    errno1 = errno;

    errno = 0;
    c2 = mulle_buffer_fgetc( buffer);
    errno2 = errno;

    printf("%s - Read at 3: FILE*='%c' (%d) (errno=%d), mulle_buffer='%c' (%d) (errno=%d)\n",
           test_name, c1, c1, errno1, c2, c2, errno2);

    // Seek relative to current position
    errno = 0;
    res1 = fseek( fp, -2, SEEK_CUR);
    errno1 = errno;

    errno = 0;
    res2 = mulle_buffer_fseek( buffer, -2, SEEK_CUR);
    errno2 = errno;

    printf("%s - Seek -2 from current: FILE*=%d (errno=%d), mulle_buffer=%d (errno=%d)\n",
           test_name, res1, errno1, res2, errno2);

    // Write character at new position
    errno = 0;
    res1 = fputc( 'X', fp);
    errno1 = errno;

    errno = 0;
    res2 = mulle_buffer_fputc( 'X', buffer);
    errno2 = errno;

    printf("%s - Write 'X': FILE*=%d (errno=%d), mulle_buffer=%d (errno=%d)\n",
           test_name, res1, errno1, res2, errno2);

    // Seek to end
    errno = 0;
    res1 = fseek( fp, 0, SEEK_END);  // not sure why fseek fails here in "normal"
    errno1 = errno;

    errno = 0;
    res2 = mulle_buffer_fseek( buffer, 0, SEEK_END);
    errno2 = errno;

    printf("%s - Seek to end: FILE*=%d (errno=%d), mulle_buffer=%d (errno=%d)\n",
           test_name, res1, errno1, res2, errno2);

    // Get final position
    errno = 0;
    pos1 = ftell( fp);
    errno1 = errno;

    errno = 0;
    pos2 = mulle_buffer_ftell( buffer);
    errno2 = errno;

    printf("%s - Final position: FILE*=%ld (errno=%d), mulle_buffer=%ld (errno=%d)\n",
           test_name, pos1, errno1, pos2, errno2);
}

static void test_seek_tell(void)
{
    FILE *fp;
    struct mulle_buffer *buffer;
    char test_string[] =
    {
      'V', 'f', 'L', ' ',
      'B', 'o', 'c', 'h', 'u', 'm', ' ',
      '1', '8', '4', '8'
    };

    // Test case 2: Normal case with read/write
    fp = fmemopen((void*)test_string, strlen(test_string), "a+");
    buffer = mulle_buffer_fmemopen((void*)test_string, strlen(test_string), "a+");
    compare_seek_tell(fp, buffer, "Normal case");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    fp = fmemopen(NULL, 0, "w");
    buffer = mulle_buffer_fmemopen(NULL, 0, "w");
    compare_seek_tell(fp, buffer, "Empty file");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 4: Read-only file, but mulle_buffer can't do read only
    fp = fmemopen((void*)test_string, strlen(test_string), "r");
    buffer = mulle_buffer_fmemopen((void*)test_string, strlen(test_string), "r");
    compare_seek_tell(fp, buffer, "Read-only file");
    fclose(fp);
    mulle_buffer_fclose(buffer);
}

int main(int argc, const char * argv[])
{
    test_seek_tell();
    return 0;
}
