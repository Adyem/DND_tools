#include "dnd_tools.hpp"
#include <sys/stat.h>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <iostream>

int ft_create_data_dir()
{
    struct stat st;
    
    memset(&st, 0, sizeof(st));
    if (stat("data", &st) == -1)
    {
		if (errno == ENOENT)
		{
			if (mkdir("data", 0700) == -1)
			{
                std::cerr << "001-Error failed to create directory: " << strerror(errno) << std::endl;
                return (1);
			}
			else if (DEBUG == 1)
				std::cout << "Data folder created successfully" << std::endl;
		}
		else
        {
            std::cerr << "002-Error failed to stat directory: " << strerror(errno) << std::endl;
            return (1);
        }
    }
    else if (S_ISDIR(st.st_mode))
    {
        if (access("data", R_OK | W_OK) == -1)
        {
            std::cerr << "003-Error no read/write access to 'data' directory: " << strerror(errno) 
                      << std::endl;
            return (1);
        }
        if (DEBUG == 1)
            std::cout << "Data folder already exists with proper access rights" << std::endl;
    }
    else
    {
        std::cerr << "004-Error path exists but is not a directory" << std::endl;
        return (1);
    }
    return (0);
}
