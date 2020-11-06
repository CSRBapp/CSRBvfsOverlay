#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>

FILE *fopen(const char *path, const char *mode) {
  FILE *ret;

  printf("*** FOPEN(%s, %s)\n", path, mode);

  FILE *(*original_fopen)(const char *, const char *);
  original_fopen = dlsym(RTLD_NEXT, "fopen");

  ret = (*original_fopen)(path, mode);
  printf("*** FOPEN(%s, %s) RET:%p\n", path, mode, ret);
  return ret;
}

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int open(const char *pathname, int flags, ...) {
  int ret;

  printf("*** OPEN(%s, 0x%x)\n", pathname, flags);

  int (*original_open)(const char *, int);
  original_open = dlsym(RTLD_NEXT, "open");

  ret = (*original_open)(pathname, flags);
  printf("*** OPEN(%s, 0x%x) RET:%d\n", pathname, flags, ret);
  return ret;
}

#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count) {
  ssize_t ret;

  printf("*** READ(%d, %p, %ld)\n", fd, buf, count);

  int (*original_read)(int, void *, size_t);
  original_read = dlsym(RTLD_NEXT, "read");

  ret = (*original_read)(fd, buf, count);
  printf("*** READ(%d, %p, %ld) RET:%ld\n", fd, buf, count, ret);
  return ret;
}
