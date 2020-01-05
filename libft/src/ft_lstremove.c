/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:55:35 by thberrid          #+#    #+#             */
/*   Updated: 2019/04/26 14:55:52 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstremove(t_list **list, t_list *to_del, void (*del)(void *, size_t))
{
	t_list	*current;
	t_list	*previous;

	current = *list;
	previous = NULL;
	while (current)
	{
		if (current == to_del)
			break ;
		previous = current;
		current = current->next;
	}
	if (previous)
		previous->next = current->next;
	current = current->next;
	ft_lstdelone(&to_del, del);
}
