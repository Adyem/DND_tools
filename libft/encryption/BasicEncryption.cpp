#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include "../Libft/libft.hpp"
#include "../CMA/CMA.hpp"
#include "../Linux/linux_file.hpp"
#include "../CPP_class/nullptr.hpp"
#include "BasicEncryption.hpp"

void be_encrypt(char *data, size_t data_len, const char *key)
{
    uint32_t hash = 5381;
    size_t key_len = ft_strlen(key);
	for (size_t i = 0; i < key_len; ++i)
        hash = ((hash << 5) + hash) + (uint8_t)key[i];
	for (size_t i = 0; i < data_len; ++i)
        data[i] ^= (hash >> (i % 8)) & 0xFF;
	return ;
}

int be_saveGame(const char *filename, const char *data, const char *key)
{
    size_t data_len = ft_strlen(data);
    char *encryptedData = (char *)cma_malloc(data_len);
    if (!encryptedData)
        return (1);
    ft_memcpy(encryptedData, data, data_len);
    be_encrypt(encryptedData, data_len, key);
    int fd = ft_open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        cma_free(encryptedData);
        return (1);
    }
    ssize_t written = ft_write(fd, encryptedData, data_len);
    ft_close(fd);
    cma_free(encryptedData);
    if (written == (ssize_t)data_len)
        return (0);
    return (1);
}

char **be_DecryptData(char **data, const char *key)
{
    if (!data || !*data)
        return (ft_nullptr);
    size_t len = ft_strlen(*data);
    be_encrypt(*data, len, key);
    return (data);
}
