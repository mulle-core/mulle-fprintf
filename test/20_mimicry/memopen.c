#include <mulle-fprintf/mulle-fprintf.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Assuming these are defined elsewhere
extern void *mulle_buffer_fmemopen(void *buf, size_t size, const char *mode);
extern int mulle_buffer_fclose(void *buffer);

int main(void)
{
    void *buffer;
    char buf[100];
    FILE  *fp;

    // Test 1: Open with NULL buffer and "w" mode
    buffer = mulle_buffer_fmemopen(NULL, 100, "w");
    if (!buffer) {
        printf("Test 1 failed: Could not open NULL buffer in write mode\n");
        return 1;
    }
    mulle_buffer_fclose(buffer);

    // Test 2: Open with NULL buffer and "r" mode (should fail)
    buffer = mulle_buffer_fmemopen(NULL, 100, "r");
    if (buffer) {
        printf("Test 2 failed: Opened NULL buffer in read mode\n");
        mulle_buffer_fclose(buffer);
        return 1;
    }

    // Test 3: Open with existing buffer and "r" mode
    strcpy(buf, "Hello, World!");
    buffer = mulle_buffer_fmemopen(buf, strlen(buf), "r");
    if (!buffer) {
        printf("Test 3 failed: Could not open existing buffer in read mode\n");
        return 1;
    }
    mulle_buffer_fclose(buffer);

    // Test 4: Open with existing buffer and "wü" mode (should clear buffer[ 0])
    buffer = mulle_buffer_fmemopen(buf, sizeof(buf), "w+");
    if (!buffer) {
        printf("Test 4 failed: Could not open existing buffer in write mode\n");
        return 1;
    }
    if (buf[0] != '\0') {
        printf("Test 4 failed: Buffer not cleared in write mode\n");
        mulle_buffer_fclose(buffer);
        return 1;
    }
    mulle_buffer_fclose(buffer);

    // Test 5: Open with existing buffer and "a" mode
    strcpy(buf, "Hello");
    buffer = mulle_buffer_fmemopen(buf, sizeof(buf), "a");
    if (!buffer) {
        printf("Test 5 failed: Could not open existing buffer in append mode\n");
        return 1;
    }
    mulle_buffer_fclose(buffer);

    // Test 6: Open with zero size
    fp     = fmemopen( NULL, 0, "w");
    buffer = mulle_buffer_fmemopen(NULL, 0, "w");
    if (buffer && ! fp) {
        printf("Test 6 failed: Opened buffer with zero size\n");
        mulle_buffer_fclose(buffer);
        return 1;
    }
    mulle_buffer_fclose(buffer);
    fclose( fp);

    // Test 7: Open with invalid mode
    buffer = mulle_buffer_fmemopen(buf, sizeof(buf), "x");
    if (buffer) {
        printf("Test 7 failed: Opened buffer with invalid mode\n");
        mulle_buffer_fclose(buffer);
        return 1;
    }

    return 0;
}
