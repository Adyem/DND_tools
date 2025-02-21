#ifndef BASIC_ENCRYPTION_HPP
#define BASIC_ENCRYPTION_HPP

#include <string>

void		ft_encrypt(std::string &data, const std::string &key);
int			saveGame(const char *filename, const char *data, const char *key);
char		**DecryptData(char **data, const char *key);
const char	*getEncryptionKey();

#endif
