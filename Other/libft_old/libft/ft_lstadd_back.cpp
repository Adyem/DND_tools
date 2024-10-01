/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adyem <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:29:36 by adyem             #+#    #+#             */
/*   Updated: 2023/10/26 14:52:28 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*tmp;

	if (!*lst || !new_node)
	{
		*lst = new_node;
		return ;
	}
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new_node;
}
