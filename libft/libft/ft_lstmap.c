/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:41:16 by cade-oli          #+#    #+#             */
/*   Updated: 2024/11/09 12:11:41 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*new_list;
	t_list	*current_node;
	t_list	*tmp;
	void	*content;

	if (!f || !del || !lst)
		return (NULL);
	tmp = lst;
	new_list = NULL;
	current_node = NULL;
	while (tmp)
	{
		content = f(tmp->content);
		current_node = ft_lstnew(content);
		if (!current_node)
		{
			del(content);
			ft_lstclear(&new_list, (*del));
			return (new_list);
		}
		ft_lstadd_back(&new_list, current_node);
		tmp = tmp->next;
	}
	return (new_list);
}
