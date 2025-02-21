#ifndef BASIC_ENCRYPTION_HPP
#define BASIC_ENCRYPTION_HPP

#include <string>

void		be_encrypt(std::string &data, const std::string &key);
int			be_saveGame(const char *filename, const char *data, const char *key);
char		**be_DecryptData(char **data, const char *key);
const char	*be_getEncryptionKey();

#endif
