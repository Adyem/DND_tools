/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adyem <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:08:32 by adyem             #+#    #+#             */
/*   Updated: 2023/10/26 15:25:28 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*error_cleanup(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	return (NULL);
}

static void	add_to_end(t_list **head, t_list **tail, t_list *new_node)
{
	if (*head == NULL)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*tmp_tail;
	t_list	*new_node;
	void	*mapped_content;

	first = NULL;
	tmp_tail = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		mapped_content = (*f)(lst->content);
		new_node = ft_lstnew(mapped_content);
		if (!new_node)
		{
			del(mapped_content);
			error_cleanup(&first, del);
			return (NULL);
		}
		add_to_end(&first, &tmp_tail, new_node);
		lst = lst->next;
	}
	return (first);
}
