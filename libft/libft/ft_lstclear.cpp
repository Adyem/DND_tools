/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adyem <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:34:22 by adyem             #+#    #+#             */
/*   Updated: 2023/10/26 14:39:16 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	current = *lst;
	if (!lst || !*lst)
		return ;
	while (current)
	{
		next_node = current->next;
		ft_lstdelone(current, del);
		current = next_node;
	}
	*lst = NULL;
}
