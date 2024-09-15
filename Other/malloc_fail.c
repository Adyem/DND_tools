#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <execinfo.h>
#include <unistd.h>  // For write
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>   // For open
#include <stdarg.h>  // For variable arguments
#include <sys/types.h>  // For fork
#include <sys/stat.h>

#define FAILURE_RATE 1  // Failure rate in percentage (0-100)

/*

add the -rdynamic and -g flags to the makefile of the evaluated project
gcc -shared -fPIC -o malloc_fail.so malloc_fail.c -ldl -rdynamic -g
LD_PRELOAD=./malloc_fail.so ./cub3D maps/map3.cub

*/

static pthread_once_t init_once = PTHREAD_ONCE_INIT;

void initialize_random_once() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((unsigned int)(ts.tv_nsec ^ getpid()));
}

void initialize_random() {
    pthread_once(&init_once, initialize_random_once);
}

int should_fail() {
    initialize_random();
    int random_value = rand() % 100;
    return random_value < FAILURE_RATE;
}

void print_failure_message(const char *function_name) {
    const char *msg_prefix = "Simulating failure in ";
    write(STDERR_FILENO, msg_prefix, strlen(msg_prefix));
    write(STDERR_FILENO, function_name, strlen(function_name));
    write(STDERR_FILENO, "\n", 1);

    // Capture the backtrace
    void *buffer[100];
    int nptrs = backtrace(buffer, 100);

    // Use backtrace_symbols_fd to avoid malloc
    write(STDERR_FILENO, "Backtrace (most recent call last):\n", 36);
    backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO);
}

// Override malloc function
void *malloc(size_t size) {
    static void *(*real_malloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
        if (!real_malloc) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"malloc\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("malloc");
        return NULL;
    }

    return real_malloc(size);
}

// Override open function
int open(const char *pathname, int flags, ...) {
    static int (*real_open)(const char *, int, ...) = NULL;
    if (!real_open) {
        real_open = dlsym(RTLD_NEXT, "open");
        if (!real_open) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"open\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("open");
        errno = ENOMEM;
        return -1;
    }

    va_list args;
    va_start(args, flags);

    int fd;
    if (flags & O_CREAT) {
        mode_t mode = va_arg(args, mode_t);
        fd = real_open(pathname, flags, mode);
    } else {
        fd = real_open(pathname, flags);
    }

    va_end(args);
    return fd;
}

// Override fork function
pid_t fork(void) {
    static pid_t (*real_fork)(void) = NULL;
    if (!real_fork) {
        real_fork = dlsym(RTLD_NEXT, "fork");
        if (!real_fork) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"fork\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("fork");
        errno = EAGAIN;
        return -1;
    }

    return real_fork();
}

// Override dup function
int dup(int oldfd) {
    static int (*real_dup)(int) = NULL;
    if (!real_dup) {
        real_dup = dlsym(RTLD_NEXT, "dup");
        if (!real_dup) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"dup\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("dup");
        errno = EMFILE;
        return -1;
    }

    return real_dup(oldfd);
}

// Override dup2 function
int dup2(int oldfd, int newfd) {
    static int (*real_dup2)(int, int) = NULL;
    if (!real_dup2) {
        real_dup2 = dlsym(RTLD_NEXT, "dup2");
        if (!real_dup2) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"dup2\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("dup2");
        errno = EMFILE;
        return -1;
    }

    return real_dup2(oldfd, newfd);
}

// Override pthread_create function
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg) {
    static int (*real_pthread_create)(pthread_t *, const pthread_attr_t *,
                                      void *(*)(void *), void *) = NULL;
    if (!real_pthread_create) {
        real_pthread_create = dlsym(RTLD_NEXT, "pthread_create");
        if (!real_pthread_create) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"pthread_create\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("pthread_create");
        return EAGAIN;
    }

    return real_pthread_create(thread, attr, start_routine, arg);
}

// Override pthread_mutex_init function
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
    static int (*real_pthread_mutex_init)(pthread_mutex_t *, const pthread_mutexattr_t *) = NULL;
    if (!real_pthread_mutex_init) {
        real_pthread_mutex_init = dlsym(RTLD_NEXT, "pthread_mutex_init");
        if (!real_pthread_mutex_init) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"pthread_mutex_init\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("pthread_mutex_init");
        return ENOMEM;
    }

    return real_pthread_mutex_init(mutex, attr);
}

// Override pipe function
int pipe(int pipefd[2]) {
    static int (*real_pipe)(int [2]) = NULL;
    if (!real_pipe) {
        real_pipe = dlsym(RTLD_NEXT, "pipe");
        if (!real_pipe) {
            const char *error_msg = "Error in dlsym(RTLD_NEXT, \"pipe\")\n";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            _exit(1);
        }
    }

    if (should_fail()) {
        print_failure_message("pipe");
        errno = EMFILE;
        return -1;
    }

    return real_pipe(pipefd);
}
