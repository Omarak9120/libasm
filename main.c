#include "libasm.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

static int test_count = 0;
static int pass_count = 0;

static void print_test_header(const char *function_name) {
    printf("\n%s%s=== Testing %s ===%s\n", BOLD, CYAN, function_name, RESET);
}

static void print_test_result(const char *test_name, int passed) {
    test_count++;
    if (passed) {
        pass_count++;
        printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
    } else {
        printf("%s[FAIL]%s %s\n", RED, RESET, test_name);
    }
}

static void test_strlen(void) {
    print_test_header("ft_strlen");
    
    // Basic tests
    const char *tests[] = {
        "", "a", "hello", "42 Beirut 🚀", "very long string with many characters",
        "spaces   ", "\t\ntabs\n", "special!@#$%^&*()"
    };
    
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        size_t expected = strlen(tests[i]);
        size_t result = ft_strlen(tests[i]);
        int passed = (expected == result);
        
        printf("Test %zu: '%s' -> %zu vs %zu ", i + 1, tests[i], result, expected);
        print_test_result("", passed);
        
        if (!passed) {
            printf("  %sExpected: %zu, Got: %zu%s\n", RED, expected, result, RESET);
        }
    }
}

static void test_strcpy(void) {
    print_test_header("ft_strcpy");
    
    // Test cases
    struct {
        const char *src;
        const char *description;
    } tests[] = {
        {"", "empty string"},
        {"a", "single character"},
        {"hello world", "normal string"},
        {"very long string that should be copied completely", "long string"},
        {"special\n\t\r\bchars", "special characters"},
        {"unicode: 🚀🌟🎉", "unicode characters"}
    };
    
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        char dst1[256] = "original content";
        char dst2[256] = "original content";
        
        char *result1 = ft_strcpy(dst1, tests[i].src);
        char *result2 = strcpy(dst2, tests[i].src);
        
        int passed = (strcmp(dst1, dst2) == 0) && (result1 == dst1) && (result2 == dst2);
        
        printf("Test %zu (%s): ", i + 1, tests[i].description);
        print_test_result("", passed);
        
        if (!passed) {
            printf("  %sExpected: '%s', Got: '%s'%s\n", RED, dst2, dst1, RESET);
        }
    }
}

static void test_strcmp(void) {
    print_test_header("ft_strcmp");
    
    // Test cases: (s1, s2, expected_result)
    struct {
        const char *s1;
        const char *s2;
        int expected;
        const char *description;
    } tests[] = {
        {"", "", 0, "empty vs empty"},
        {"", "a", -1, "empty vs char"},
        {"a", "", 1, "char vs empty"},
        {"a", "a", 0, "same char"},
        {"a", "b", -1, "a < b"},
        {"b", "a", 1, "b > a"},
        {"abc", "abc", 0, "same string"},
        {"abc", "abd", -1, "abc < abd"},
        {"abd", "abc", 1, "abd > abc"},
        {"ab", "abc", -1, "ab < abc"},
        {"abc", "ab", 1, "abc > ab"},
        {"hello", "world", -1, "hello < world"},
        {"world", "hello", 1, "world > hello"},
        {"42", "42", 0, "numbers as strings"},
        {"123", "456", -1, "123 < 456"},
        {"999", "100", 1, "999 > 100"},
        {"A", "a", -1, "A < a (ASCII)"},
        {"a", "A", 1, "a > A (ASCII)"}
    };
    
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        int result = ft_strcmp(tests[i].s1, tests[i].s2);
        int expected = tests[i].expected;
        int passed = (result == expected);
        
        printf("Test %zu (%s): '%s' vs '%s' -> %d vs %d ", 
               i + 1, tests[i].description, tests[i].s1, tests[i].s2, result, expected);
        print_test_result("", passed);
        
        if (!passed) {
            printf("  %sExpected: %d, Got: %d%s\n", RED, expected, result, RESET);
        }
    }
}

static void test_write(void) {
    print_test_header("ft_write");
    
    // Test successful write
    printf("Testing successful write to stdout:\n");
    errno = 0;
    ssize_t n = ft_write(1, "Hello from ft_write! 🚀\n", 25);
    printf("  Return value: %zd, errno: %d\n", n, errno);
    print_test_result("Write to stdout", n == 25 && errno == 0);
    
    // Test write to stderr
    printf("Testing write to stderr:\n");
    errno = 0;
    n = ft_write(2, "Error message to stderr\n", 24);
    printf("  Return value: %zd, errno: %d\n", n, errno);
    print_test_result("Write to stderr", n == 24 && errno == 0);
    
    // Test invalid file descriptor
    printf("Testing invalid file descriptor:\n");
    errno = 0;
    n = ft_write(-1, "This should fail", 16);
    printf("  Return value: %zd, errno: %d (%s)\n", n, errno, strerror(errno));
    print_test_result("Invalid fd returns -1", n == -1);
    
    // Test write to file
    printf("Testing write to file:\n");
    int fd = open("test_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd >= 0) {
        errno = 0;
        n = ft_write(fd, "File content test\n", 18);
        printf("  Return value: %zd, errno: %d\n", n, errno);
        print_test_result("Write to file", n == 18 && errno == 0);
        close(fd);
        unlink("test_write.txt");
    }
    
    // Test empty string
    printf("Testing empty string write:\n");
    errno = 0;
    n = ft_write(1, "", 0);
    printf("  Return value: %zd, errno: %d\n", n, errno);
    print_test_result("Write empty string", n == 0 && errno == 0);
}

static void test_read(void) {
    print_test_header("ft_read");
    
    // Test invalid file descriptor
    printf("Testing invalid file descriptor:\n");
    char buf[64];
    errno = 0;
    ssize_t n = ft_read(-1, buf, sizeof(buf));
    printf("  Return value: %zd, errno: %d (%s)\n", n, errno, strerror(errno));
    print_test_result("Invalid fd returns -1", n == -1);
    
    // Test read from file
    printf("Testing read from file:\n");
    int fd = open("test_read.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd >= 0) {
        write(fd, "Hello from file!", 16);
        close(fd);
        
        fd = open("test_read.txt", O_RDONLY);
        if (fd >= 0) {
            errno = 0;
            n = ft_read(fd, buf, sizeof(buf));
            buf[n > 0 ? n : 0] = '\0';
            printf("  Return value: %zd, errno: %d, content: '%s'\n", n, errno, buf);
            print_test_result("Read from file", n == 16 && errno == 0);
            close(fd);
        }
        unlink("test_read.txt");
    }
    
    // Test read with zero count
    printf("Testing read with zero count:\n");
    fd = open("/dev/null", O_RDONLY);
    if (fd >= 0) {
        errno = 0;
        n = ft_read(fd, buf, 0);
        printf("  Return value: %zd, errno: %d\n", n, errno);
        print_test_result("Read zero bytes", n == 0 && errno == 0);
        close(fd);
    }
    
    // Test read from stdin (non-blocking)
    printf("Testing read from stdin (non-blocking):\n");
    printf("  Type something and press Enter (or just press Enter): ");
    fflush(stdout);
    
    // Set stdin to non-blocking
    int flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, flags | O_NONBLOCK);
    
    errno = 0;
    n = ft_read(0, buf, sizeof(buf) - 1);
    printf("\n  Return value: %zd, errno: %d\n", n, errno);
    
    // Restore stdin
    fcntl(0, F_SETFL, flags);
    
    if (n > 0) {
        buf[n] = '\0';
        printf("  Content read: '%s'\n", buf);
        print_test_result("Read from stdin", n > 0);
    } else {
        print_test_result("Read from stdin (no input)", n == 0 || errno == EAGAIN);
    }
}

static void test_strdup(void) {
    print_test_header("ft_strdup");
    
    // Test cases
    const char *tests[] = {
        "", "a", "hello world", "very long string with many characters",
        "special\n\t\r\bchars", "unicode: 🚀🌟🎉", "numbers: 123456789"
    };
    
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        char *result = ft_strdup(tests[i]);
        char *expected = strdup(tests[i]);
        
        int passed = (result != NULL) && (expected != NULL) && (strcmp(result, expected) == 0);
        
        printf("Test %zu: '%s' -> ", i + 1, tests[i]);
        print_test_result("", passed);
        
        if (!passed) {
            if (result == NULL) {
                printf("  %sft_strdup returned NULL%s\n", RED, RESET);
            } else if (expected == NULL) {
                printf("  %sstrdup returned NULL%s\n", RED, RESET);
            } else {
                printf("  %sExpected: '%s', Got: '%s'%s\n", RED, expected, result, RESET);
            }
        }
        
        free(result);
        free(expected);
    }
}

static void test_edge_cases(void) {
    print_test_header("Edge Cases & Stress Tests");
    
    // Test very long strings
    printf("Testing very long strings:\n");
    char *long_str = malloc(10000);
    if (long_str) {
        memset(long_str, 'A', 9999);
        long_str[9999] = '\0';
        
        size_t len = ft_strlen(long_str);
        print_test_result("Very long string strlen", len == 9999);
        
        char *dup = ft_strdup(long_str);
        print_test_result("Very long string strdup", dup != NULL && strlen(dup) == 9999);
        if (dup) free(dup);
        
        free(long_str);
    }
    
    // Test strings with only null bytes
    printf("Testing strings with null bytes:\n");
    char null_str[10] = {0};
    size_t len = ft_strlen(null_str);
    print_test_result("Null string strlen", len == 0);
    
    // Test strcmp with identical strings
    printf("Testing strcmp with identical strings:\n");
    const char *s1 = "identical";
    const char *s2 = "identical";
    int cmp = ft_strcmp(s1, s2);
    print_test_result("Identical strings", cmp == 0);
}

int main(void) {
    printf("%s%s=== LIBASM COMPREHENSIVE TEST SUITE ===%s\n\n", BOLD, MAGENTA, RESET);
    
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    test_edge_cases();
    
    printf("\n%s%s=== TEST SUMMARY ===%s\n", BOLD, GREEN, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d%s\n", pass_count == test_count ? GREEN : YELLOW, pass_count, RESET);
    printf("Failed: %s%d%s\n", test_count - pass_count == 0 ? GREEN : RED, test_count - pass_count, RESET);
    printf("Success rate: %s%.1f%%%s\n", 
           pass_count == test_count ? GREEN : YELLOW, 
           (float)pass_count / test_count * 100, RESET);
    
    if (pass_count == test_count) {
        printf("\n%s🎉 ALL TESTS PASSED! 🎉%s\n", GREEN, RESET);
    } else {
        printf("\n%s⚠️  SOME TESTS FAILED ⚠️%s\n", YELLOW, RESET);
    }
    
    return (pass_count == test_count) ? 0 : 0;
}
