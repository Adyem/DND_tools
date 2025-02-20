#ifndef BASIC_ENCRYPTION_HPP
#define BASIC_ENCRYPTION_HPP

#include <string>

namespace BasicEncryption
{
    void customEncrypt(std::string &data, const std::string &key);
    bool saveGame(const std::string &filename, const std::string &data, const std::string &key);
    bool loadGame(const std::string &filename, std::string &data, const std::string &key);
    std::string getEncryptionKey();
}

#endif
