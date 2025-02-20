#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Encrypts (or decrypts) data in-place.
// data: pointer to the buffer to encrypt/decrypt.
// data_len: length of the data buffer.
// key: C-string key used for encryption.
void ft_encrypt(char *data, size_t data_len, const char *key) {
    uint32_t hash = 5381;
    size_t key_len = strlen(key);
    for (size_t i = 0; i < key_len; ++i)
        hash = ((hash << 5) + hash) + (uint8_t)key[i];
    for (size_t i = 0; i < data_len; ++i)
        data[i] ^= (hash >> (i % 8)) & 0xFF;
}

// Saves the game data to a file after encrypting it.
// filename: path to the output file.
// data: pointer to the game data buffer.
// data_len: length of the game data.
// key: encryption key (C-string).
// Returns 1 on success, 0 on failure.
int saveGame(const char *filename, const char *data, size_t data_len, const char *key) {
    // Make a copy of data because encryption is in-place.
    char *encryptedData = (char *)malloc(data_len);
    if (!encryptedData)
        return 0;
    memcpy(encryptedData, data, data_len);
    ft_encrypt(encryptedData, data_len, key);

    FILE *outFile = fopen(filename, "wb");
    if (!outFile) {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        free(encryptedData);
        return 0;
    }
    size_t written = fwrite(encryptedData, 1, data_len, outFile);
    fclose(outFile);
    free(encryptedData);
    return (written == data_len) ? 1 : 0;
}

// Loads game data from a file, decrypting it after reading.
// filename: path to the input file.
// data: pointer to a char* that will be set to the allocated buffer containing the data.
// data_len: pointer to a size_t that will receive the length of the data.
// key: encryption key (C-string).
// Returns 1 on success, 0 on failure.
// Note: Caller must free the allocated *data.
int loadGame(const char *filename, char **data, size_t *data_len, const char *key) {
    FILE *inFile = fopen(filename, "rb");
    if (!inFile) {
        fprintf(stderr, "Error opening file for reading: %s\n", filename);
        return 0;
    }
    fseek(inFile, 0, SEEK_END);
    long size = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);
    if (size <= 0) {
        fprintf(stderr, "Empty or invalid file: %s\n", filename);
        fclose(inFile);
        return 0;
    }
    char *buffer = (char *)malloc(size);
    if (!buffer) {
        fclose(inFile);
        return 0;
    }
    size_t read_bytes = fread(buffer, 1, size, inFile);
    fclose(inFile);
    if (read_bytes != (size_t)size) {
        free(buffer);
        return 0;
    }
    // Decrypt in-place.
    ft_encrypt(buffer, size, key);
    *data = buffer;
    *data_len = size;
    return 1;
}

// Constructs an encryption key by concatenating a fixed salt with the current user's name.
// Returns a dynamically allocated C-string containing "SecretSalt_<username>".
// The caller is responsible for freeing the returned string.
char *getEncryptionKey(void) {
    const char *user = getenv("USER");
    if (!user)
        user = getenv("USERNAME");
    if (!user)
        user = "default_user";

    const char *prefix = "SecretSalt_";
    size_t prefix_len = strlen(prefix);
    size_t user_len = strlen(user);
    size_t total_len = prefix_len + user_len + 1; // +1 for null terminator

    char *result = (char *)malloc(total_len);
    if (!result)
        return NULL;
    strcpy(result, prefix);
    strcat(result, user);
    return result;
}
