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

static size_t safe_fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t result;
    if (setjmp(jump_buffer) == 0)
    {
        result = fread(ptr, size, nmemb, stream);
    }
    else
    {
        result = (size_t)-1;  // Special value to indicate crash
    }
    return result;
}

static size_t safe_mulle_buffer_fread(void *ptr, size_t size, size_t nmemb, void *buffer)
{
    size_t result;
    if (setjmp(jump_buffer) == 0)
    {
        result = mulle_buffer_fread(ptr, size, nmemb, buffer);
    }
    else
    {
        result = (size_t)-1;  // Special value to indicate crash
    }
    return result;
}

static void compare_read(void *ptr1, void *ptr2, size_t size, size_t nmemb, FILE *fp, void *buffer, const char *test_name)
{
    size_t r1, r2;
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
    r1 = safe_fread(ptr1, size, nmemb, fp);
    errno1 = errno;

    errno = 0;
    r2 = safe_mulle_buffer_fread(ptr2, size, nmemb, buffer);
    errno2 = errno;

    if (r1 == r2 && errno1 == errno2)
    {
        if (r1 == (size_t)-1)
        {
            printf("%s: Passed (both crashed as expected)\n", test_name);
        }
        else if (memcmp(ptr1, ptr2, r1 * size) == 0)
        {
            printf("%s: Passed (result=%zu, errno=%d)\n", test_name, r1, errno1);
        }
        else
        {
            printf("%s: Failed (result=%zu, errno=%d, but data mismatch)\n", test_name, r1, errno1);
        }
    }
    else
    {
        printf("Error in %s: fread: result=%zu, errno=%d; mulle_buffer_fread: result=%zu, errno=%d\n",
               test_name, r1, errno1, r2, errno2);
    }

    signal(SIGSEGV, SIG_DFL);  // Reset signal handler
}

static void test_read(void)
{
    FILE *fp;
    void *buffer;
    const char test_data[] = "Hello, World!";
    char read_buf1[20], read_buf2[20];

    // Test case 1: Read from memory stream
    fp = fmemopen((void*)test_data, strlen(test_data), "r");
    buffer = mulle_buffer_fmemopen((void*)test_data, strlen(test_data), "r");
    compare_read(read_buf1, read_buf2, 1, strlen(test_data), fp, buffer, "Read from memory stream");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 2: Read more than available
    fp = fmemopen((void*)test_data, strlen(test_data), "r");
    buffer = mulle_buffer_fmemopen((void*)test_data, strlen(test_data), "r");
    compare_read(read_buf1, read_buf2, 1, 20, fp, buffer, "Read more than available");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 3: Read-only empty file
    fp = fmemopen("", 0, "r");
    buffer = mulle_buffer_fmemopen("", 0, "r");
    compare_read(read_buf1, read_buf2, 1, 10, fp, buffer, "Read-only empty file");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 4: Multiple reads
    fp = fmemopen((void*)test_data, strlen(test_data), "r");
    buffer = mulle_buffer_fmemopen((void*)test_data, strlen(test_data), "r");
    for (int i = 0; i < 5; i++)
    {
        compare_read(read_buf1, read_buf2, 1, 2, fp, buffer, "Multiple reads");
    }
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 5: Read with different size and nmemb
    fp = fmemopen((void*)test_data, strlen(test_data), "r");
    buffer = mulle_buffer_fmemopen((void*)test_data, strlen(test_data), "r");
    compare_read(read_buf1, read_buf2, 2, strlen(test_data) / 2, fp, buffer, "Read with size=2, nmemb=6");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 6: NULL pointers
    compare_read(read_buf1, read_buf2, 1, strlen(test_data), NULL, NULL, "NULL pointers");
}

int main(int argc, const char * argv[])
{
    test_read();
    return 0;
}
