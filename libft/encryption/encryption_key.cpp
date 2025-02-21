#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include "../CMA/CMA.hpp"
#include "../CPP_class/nullptr.hpp"
#include "BasicEncryption.hpp"

static void decoy_unusedFunction1(void)
{
    volatile int dummy = 0;
	for (int i = 0; i < 10; i++)
        dummy += i;
	return ;
}

static uint32_t decoy_unusedFunction2(uint32_t x)
{
    x ^= 0xAAAAAAAA;
    x ^= 0xAAAAAAAA;
    return (x);
}

static int decoy_unusedFunction3(const char* input)
{
    (void)input;
    return (42);
}

static uint32_t obfuscate_seed(uint32_t seed)
{
    decoy_unusedFunction1();
    seed = decoy_unusedFunction2(seed);
    return (seed);
}

const char *be_getEncryptionKey(void)
{
    size_t key_len = 32;
    char *key = (char *)cma_malloc(key_len + 1);
    if (!key)
        return (ft_nullptr);
    uint32_t seed = 0xDEADBEEF;
    seed = obfuscate_seed(seed);
    for (size_t i = 0; i < key_len; i++)
    {
        decoy_unusedFunction3(key);
        seed = seed * 1103515245 + 12345;
        key[i] = 'A' + (seed % 26);
    }
    key[key_len] = '\0';
    decoy_unusedFunction1();
    return (key);
}
