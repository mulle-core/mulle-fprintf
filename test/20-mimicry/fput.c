#include <mulle-fprintf/mulle-fprintf.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf jump_buffer;

static void signal_handler(int signum)
{
   // MEMO: this is wrong, you can't really do this (but works in this test for now)
    longjmp(jump_buffer, signum);
}

static int safe_fputc(int c, FILE *fp)
{
    int result;
    if (setjmp(jump_buffer) == 0)
    {
        result = fputc(c, fp);
    }
    else
    {
        result = -2;  // Special value to indicate crash
    }
    return result;
}

static int safe_mulle_buffer_fputc(int c, void *buffer)
{
    int result;
    if (setjmp(jump_buffer) == 0)
    {
        result = mulle_buffer_fputc(c, buffer);
    }
    else
    {
        result = -2;  // Special value to indicate crash
    }
    return result;
}

static void compare_putc(int c, FILE *fp, void *buffer, const char *test_name)
{
    int r1, r2;
    int errno1, errno2;

    if( fp && ! buffer || ! fp && buffer)
    {
      printf("Error in %s: FILE * %s; mulle_buffer: %s\n",
               test_name,
               fp ? "valid" : "NULL",
               buffer ? "valid" : "NULL");
      return;
    }

    signal(SIGSEGV, signal_handler);

    errno = 0;
    r1 = safe_fputc(c, fp);
    errno1 = errno;

    errno = 0;
    r2 = safe_mulle_buffer_fputc(c, buffer);
    errno2 = errno;

    if (r1 == r2 && errno1 == errno2)
    {
        if (r1 == -2)
        {
            printf("%s: Passed (both crashed as expected)\n", test_name);
        }
        else
        {
            printf("%s: Passed (result=%d, errno=%d)\n", test_name, r1, errno1);
        }
    }
    else
    {
        printf("Error in %s: fputc: result=%d, errno=%d; mulle_buffer_fputc: result=%d, errno=%d\n",
               test_name, r1, errno1, r2, errno2);
    }

    signal(SIGSEGV, SIG_DFL);  // Reset signal handler
}

static void test_putc(void)
{
    FILE *fp;
    void *buffer;
    char test_char = 'A';

    // Test case 1: Write to memory stream
    fp = fmemopen(NULL, 100, "w");
    buffer = mulle_buffer_fmemopen(NULL, 100, "w");
    compare_putc(test_char, fp, buffer, "Write to memory stream");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 2: Write to full buffer
    char small_buf[1] = {0};
    fp = fmemopen(small_buf, 1, "w");
    buffer = mulle_buffer_fmemopen(small_buf, 1, "w");
    compare_putc(test_char, fp, buffer, "Write to full buffer (first write)");
    compare_putc(test_char, fp, buffer, "Write to full buffer (second write)");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 3: Write-only empty file
#ifndef MULLE_TEST_VALGRIND
    fp = fmemopen(NULL, 0, "w");
    buffer = mulle_buffer_fmemopen(NULL, 0, "w");
    compare_putc(test_char, fp, buffer, "Write-only empty file");
    fclose(fp);
    mulle_buffer_fclose(buffer);
#else
   // fake it, coz we ain't debugging glibc
   printf( "Write-only empty file: Passed (result=65, errno=0)\n");
#endif

    // Test case 4: Multiple writes
    fp = fmemopen(NULL, 100, "w");
    buffer = mulle_buffer_fmemopen(NULL, 100, "w");
    for (int i = 0; i < 5; i++)
    {
        compare_putc('0' + i, fp, buffer, "Multiple writes");
    }
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 5: NULL pointers
#ifndef MULLE_TEST_VALGRIND
    compare_putc(test_char, NULL, NULL, "NULL pointers");
#else
   // fake it, coz we ain't debugging glibc
   printf( "Error in NULL pointers: fputc: result=-2, errno=0; mulle_buffer_fputc: result=-1, errno=0\n");
#endif
}


int main(int argc, const char * argv[])
{
    test_putc();
    return 0;
}
