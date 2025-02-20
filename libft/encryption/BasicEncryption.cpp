#include "BasicEncryption.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdint>

namespace BasicEncryption
{
    void customEncrypt(std::string &data, const std::string &key)
	{
        uint32_t hash = 5381;
        for (size_t i = 0; i < key.size(); ++i)
            hash = ((hash << 5) + hash) + static_cast<uint8_t>(key[i]);
        for (size_t i = 0; i < data.size(); ++i)
            data[i] ^= (hash >> (i % 8)) & 0xFF;
    }

    bool saveGame(const std::string &filename, const std::string &data, const std::string &key)
	{
        std::string encryptedData = data;
        customEncrypt(encryptedData, key);
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile)
		{
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return false;
        }
        outFile.write(encryptedData.data(), encryptedData.size());
        outFile.close();
        return true;
    }

    bool loadGame(const std::string &filename, std::string &data, const std::string &key)
	{
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile)
		{
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return false;
        }
        inFile.seekg(0, std::ios::end);
        std::streamsize size = inFile.tellg();
        inFile.seekg(0, std::ios::beg);
        if (size <= 0)
		{
            std::cerr << "Empty or invalid file: " << filename << std::endl;
            return false;
        }
        data.resize(size);
        inFile.read(&data[0], size);
        inFile.close();
        customEncrypt(data, key);
        return true;
    }

    std::string getEncryptionKey()
	{
        const char* user = std::getenv("USER");
        if (!user)
            user = std::getenv("USERNAME");
        std::string username = (user ? user : "default_user");
        return "SecretSalt_" + username;
    }
}
