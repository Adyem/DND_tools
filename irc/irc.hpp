#ifndef IRC_HPP
# define IRC_HPP

#ifndef DEBUG
# define DEBUG 0
#endif

#define MAX_CLIENTS 100
#define NULL_PTR (reinterpret_cast<void*>(0))

#include "server_class.hpp"

int		ft_check_input(char *input);
Server	*ft_create_socket(int port, char *password);
void	ft_start_server(Server *info_server);

#endif
