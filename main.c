#include "libasm.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void test_strlen(void) {
    const char *a = "", *b = "hello", *c = "42 Beirut 🚀";
    printf("[strlen] '' -> %zu (lib) vs %zu (libc)\n", ft_strlen(a), strlen(a));
    printf("[strlen] 'hello' -> %zu vs %zu\n", ft_strlen(b), strlen(b));
    printf("[strlen] '42 Beirut 🚀' -> %zu vs %zu\n", ft_strlen(c), strlen(c));
}

static void test_strcpy(void) {
    char dst1[64], dst2[64];
    const char *src = "copy me";
    printf("[strcpy] -> '%s' vs '%s'\n",
           ft_strcpy(dst1, src),
           strcpy(dst2, src));
}

static void test_strcmp(void) {
    printf("[strcmp] 'abc','abc' -> %d vs %d\n", ft_strcmp("abc","abc"), strcmp("abc","abc"));
    printf("[strcmp] 'abc','abd' -> %d vs %d\n", ft_strcmp("abc","abd"), strcmp("abc","abd"));
    printf("[strcmp] 'abd','abc' -> %d vs %d\n", ft_strcmp("abd","abc"), strcmp("abd","abc"));
    printf("[strcmp] '','a'     -> %d vs %d\n", ft_strcmp("","a"), strcmp("","a"));
}

static void test_write(void) {
    errno = 0;
    ssize_t n = ft_write(1, "Hello via ft_write\n", 20);
    printf("[write] ok -> ret=%zd errno=%d\n", n, errno);

    errno = 0;
    n = ft_write(-1, "bad fd\n", 7);
    printf("[write] bad fd -> ret=%zd errno=%d (%s)\n", n, errno, strerror(errno));
}

static void test_read(void) {
    char buf[8] = {0};
    errno = 0;
    ssize_t n = ft_read(-1, buf, sizeof(buf));
    printf("[read] bad fd -> ret=%zd errno=%d (%s)\n", n, errno, strerror(errno));
    // Optional interactive test:
    // printf("Type up to 7 chars: ");
    // fflush(stdout);
    // n = ft_read(0, buf, 7);
    // if (n >= 0) buf[n] = '\0';
    // printf("\n[read] read=%zd buf='%s'\n", n, buf);
}

static void test_strdup(void) {
    const char *s = "duplicate me";
    char *mine = ft_strdup(s);
    char *ref  = strdup(s);
    printf("[strdup] -> '%s' vs '%s'\n", mine, ref);
    free(mine);
    free(ref);
}

int main(void) {
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    return 0;
}
