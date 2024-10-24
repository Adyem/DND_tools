#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

static void ft_add_player(t_pc *player) {
  int fd;
  char *filename;

  filename = cma_strjoin("data/PC--", player->name, false);
  if (!filename)
  {
    ft_printf("240-Error: Allocating memory for player string join\n");
    return ;
  }
  fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  cma_free(filename);
  if (fd == -1)
  {
    ft_printf("Error opening file: %s\n", strerror(errno));
    return ;
  }
  ft_printf("Adding player %s\n", player->name);
  ft_save_pc(player, fd);
  close(fd);
  return ;
}

void ft_player(const char **input)
{
  t_pc *player = nullptr;

  if (input[1] && input[2]) {
    if (ft_strcmp_dnd(input[0], "add") == 0)
	{
      player = (t_pc *)cma_malloc(sizeof(t_pc), false);
      if (!player) {
        ft_printf("248-Error: Allocating memory for player\n");
        return ;
      }
      player->name = cma_strdup(input[2], false);
      if (!player->name) {
        ft_printf("249-Error: Allocating memory for player name\n");
        cma_free(player);
        return ;
      }
      player->initiative = 0;
      ft_add_player(player);
    }
  }
  else
    ft_printf("243-Error: Invalid input for player\n");
  cma_free(player->name);
  cma_free(player);
  return ;
}
