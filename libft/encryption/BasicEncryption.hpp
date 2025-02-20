#ifndef BASIC_ENCRYPTION_HPP
#define BASIC_ENCRYPTION_HPP

#include <string>

void ft_encrypt(std::string &data, const std::string &key);
bool saveGame(const std::string &filename, const std::string &data, const std::string &key);
bool loadGame(const std::string &filename, std::string &data, const std::string &key);
const char *getEncryptionKey();

#endif
