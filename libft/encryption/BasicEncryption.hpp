#ifndef BASIC_ENCRYPTION_HPP
#define BASIC_ENCRYPTION_HPP

#include <string>

void		ft_encrypt(std::string &data, const std::string &key);
int			saveGame(const std::string &filename, const std::string &data,
						const std::string &key);
char		**DecryptData(char **data);
const char	*getEncryptionKey();

#endif
