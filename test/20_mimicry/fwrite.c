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

static size_t safe_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t result;
    if (setjmp(jump_buffer) == 0)
    {
        result = fwrite(ptr, size, nmemb, stream);
    }
    else
    {
        result = (size_t)-1;  // Special value to indicate crash
    }
    return result;
}

static size_t safe_mulle_buffer_fwrite(const void *ptr, size_t size, size_t nmemb, void *buffer)
{
    size_t result;
    if (setjmp(jump_buffer) == 0)
    {
        result = mulle_buffer_fwrite(ptr, size, nmemb, buffer);
    }
    else
    {
        result = (size_t)-1;  // Special value to indicate crash
    }
    return result;
}

static void compare_write(const void *ptr, size_t size, size_t nmemb, FILE *fp, void *buffer, const char *test_name)
{
    size_t r1, r2;
    int errno1, errno2;

    signal(SIGSEGV, signal_handler);

    errno = 0;
    r1 = safe_fwrite(ptr, size, nmemb, fp);
    errno1 = errno;

    errno = 0;
    r2 = safe_mulle_buffer_fwrite(ptr, size, nmemb, buffer);
    errno2 = errno;

    if (r1 == r2 && errno1 == errno2)
    {
        if (r1 == (size_t)-1)
        {
            printf("%s: Passed (both crashed as expected)\n", test_name);
        }
        else
        {
            printf("%s: Passed (result=%zu, errno=%d)\n", test_name, r1, errno1);
        }
    }
    else
    {
        printf("Error in %s: fwrite: result=%zu, errno=%d; mulle_buffer_fwrite: result=%zu, errno=%d\n",
               test_name, r1, errno1, r2, errno2);
    }

    signal(SIGSEGV, SIG_DFL);  // Reset signal handler
}

static void test_write(void)
{
    FILE *fp;
    void *buffer;
    const char test_data[] = "Hello, World!";

    // Test case 1: NULL pointers
    compare_write(test_data, 1, strlen(test_data), NULL, NULL, "NULL pointers");

    // Test case 2: Write to memory stream
    fp = fmemopen(NULL, 100, "w");
    buffer = mulle_buffer_fmemopen(NULL, 100, "w");
    compare_write(test_data, 1, strlen(test_data), fp, buffer, "Write to memory stream");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 3: Write to full buffer
    char small_buf[5] = {0};
    fp = fmemopen(small_buf, 5, "w");
    buffer = mulle_buffer_fmemopen(small_buf, 5, "w");
    compare_write(test_data, 1, strlen(test_data), fp, buffer, "Write to full buffer");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 4: Write-only empty file
    fp = fmemopen(NULL, 0, "w");
    buffer = mulle_buffer_fmemopen(NULL, 0, "w");
    compare_write(test_data, 1, strlen(test_data), fp, buffer, "Write-only empty file");
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 5: Multiple writes
    fp = fmemopen(NULL, 100, "w");
    buffer = mulle_buffer_fmemopen(NULL, 100, "w");
    for (int i = 0; i < 5; i++)
    {
        char chunk[3] = {0};
        snprintf(chunk, sizeof(chunk), "%d", i);
        compare_write(chunk, 1, strlen(chunk), fp, buffer, "Multiple writes");
    }
    fclose(fp);
    mulle_buffer_fclose(buffer);

    // Test case 6: Write with different size and nmemb
    fp = fmemopen(NULL, 100, "w");
    buffer = mulle_buffer_fmemopen(NULL, 100, "w");
    compare_write(test_data, 2, strlen(test_data) / 2, fp, buffer, "Write with size=2, nmemb=6");
    fclose(fp);
    mulle_buffer_fclose(buffer);
}

int main(int argc, const char * argv[])
{
    test_write();
    return 0;
}
