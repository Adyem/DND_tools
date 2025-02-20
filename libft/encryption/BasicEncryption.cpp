#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include "../Libft/libft.hpp"
#include "../CMA/CMA.hpp"
#include "../Linux/linux_file.hpp"
#include "../CPP_class/nullptr.hpp"
#include "BasicEncryption.hpp"

void ft_encrypt(char *data, size_t data_len, const char *key)
{
    uint32_t hash = 5381;
    size_t key_len = ft_strlen(key);
	for (size_t i = 0; i < key_len; ++i)
        hash = ((hash << 5) + hash) + (uint8_t)key[i];
	for (size_t i = 0; i < data_len; ++i)
        data[i] ^= (hash >> (i % 8)) & 0xFF;
	return ;
}

int saveGame(const char *filename, const char *data, size_t data_len, const char *key)
{
    char *encryptedData = (char *)cma_malloc(data_len);
    if (!encryptedData)
        return (1);
    ft_memcpy(encryptedData, data, data_len);
    ft_encrypt(encryptedData, data_len, key);
    int fd = ft_open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        free(encryptedData);
        return (1);
    }
    ssize_t written = ft_write(fd, encryptedData, data_len);
    ft_close(fd);
    free(encryptedData);
    
    if (written == (ssize_t)data_len)
        return (0);
    return (1);
}

char **DecryptData(char **data)
{
    if (!data || !*data)
        return (ft_nullptr);
    const char *key = getEncryptionKey();
    size_t len = ft_strlen(*data);
    ft_encrypt(*data, len, key);
    return (data);
}

const char *getEncryptionKey(void)
{
    const char *key = "SecretSalt_8yt4b9zliw7u3th";
    return (key);
}
