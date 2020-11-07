#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


static FILE *(*original_fopen)(const char *, const char *) = NULL;
static int (*original_open)(const char *, int) = NULL;
static ssize_t (*original_read)(int, void *, size_t) = NULL;
static ssize_t (*original_write)(int, const void *, size_t) = NULL;
static int (*original_stat)(const char *, struct stat *) = NULL;
static int (*original_fstat)(int, struct stat *) = NULL;
static int (*original_lstat)(const char *, struct stat *) = NULL;
static int (*original_fstatat)(int, const char *, struct stat *, int);


void CSRBvfsOverlayInit(void) {
  static int initialised = 0;
  if (initialised)
    return;
  initialised = 1;

  fprintf(stderr, "*** INIT\n");
  original_fopen = dlsym(RTLD_NEXT, "fopen");
  original_open = dlsym(RTLD_NEXT, "open");
  original_read = dlsym(RTLD_NEXT, "read");
  original_write = dlsym(RTLD_NEXT, "write");
  original_stat = dlsym(RTLD_NEXT, "stat");
  original_fstat = dlsym(RTLD_NEXT, "fstat");
  original_lstat = dlsym(RTLD_NEXT, "lstat");
}

FILE *fopen(const char *path, const char *mode) {
  FILE *ret;
  CSRBvfsOverlayInit();
  fprintf(stderr, "*** FOPEN(%s, %s)\n", path, mode);
  ret = (*original_fopen)(path, mode);
  fprintf(stderr, "*** FOPEN(%s, %s) RET:%p\n", path, mode, ret);
  return ret;
}

int open(const char *pathname, int flags, ...) {
  int ret;
  fprintf(stderr, "*** OPEN(%s, 0x%x)\n", pathname, flags);
  ret = (*original_open)(pathname, flags);
  fprintf(stderr, "*** OPEN(%s, 0x%x) RET:%d\n", pathname, flags, ret);
  return ret;
}

ssize_t read(int fd, void *buf, size_t count) {
  ssize_t ret;
  fprintf(stderr, "*** READ(%d, %p, %ld)\n", fd, buf, count);
  ret = (*original_read)(fd, buf, count);
  fprintf(stderr, "*** READ(%d, %p, %ld) RET:%ld\n", fd, buf, count, ret);
  return ret;
}

ssize_t write(int fd, const void *buf, size_t count) {
  ssize_t ret;
  fprintf(stderr, "*** WRITE(%d, %p, %ld)\n", fd, buf, count);
  ret = (*original_write)(fd, buf, count);
  fprintf(stderr, "*** WRITE(%d, %p, %ld) RET:%ld\n", fd, buf, count, ret);
  return ret;
}

int stat(const char *pathname, struct stat *statbuf) {
  int ret;
  fprintf(stderr, "*** STAT(%s, %p)\n", pathname, statbuf);
  ret = (*original_stat)(pathname, statbuf);
  fprintf(stderr, "*** STAT(%s, %p) RET:%d\n", pathname, statbuf, ret);
  return ret;
}

int fstat(int fd, struct stat *statbuf) {
  int ret;
  fprintf(stderr, "*** FSTAT(%d, %p)\n", fd, statbuf);
  ret = (*original_fstat)(fd, statbuf);
  fprintf(stderr, "*** FSTAT(%d, %p) RET:%d\n", fd, statbuf, ret);
  return ret;
}

int lstat(const char *pathname, struct stat *statbuf) {
  int ret;
  fprintf(stderr, "*** LSTAT(%s, %p)\n", pathname, statbuf);
  ret = (*original_lstat)(pathname, statbuf);
  fprintf(stderr, "*** LSTAT(%s, %p) RET:%d\n", pathname, statbuf, ret);
  return ret;
}

int fstatat(int dirfd, const char *pathname, struct stat *statbuf, int flags) {
  int ret;
  fprintf(stderr, "*** FSTATAT(%d, %s, %p, %d)\n", dirfd, pathname, statbuf, flags);
  ret = (*original_fstatat)(dirfd, pathname, statbuf, flags);
  fprintf(stderr, "*** FSTATAT(%d, %s, %p, %d) RET:%d\n", dirfd, pathname, statbuf, flags, ret);
  return ret;
}
