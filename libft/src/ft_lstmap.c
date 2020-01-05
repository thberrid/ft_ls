/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 20:21:37 by thberrid          #+#    #+#             */
/*   Updated: 2019/05/08 21:30:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_link;

	new_link = ft_lstnew((f(lst))->content, (f(lst))->content_size);
	if (new_link)
	{
		new_link->next = NULL;
		lst = lst->next;
		if (lst)
		{
			new_link->next = ft_lstmap(lst, f);
			if (!new_link->next)
			{
				ft_lstdelone(&new_link, &ft_bzero);
				return (NULL);
			}
		}
	}
	return (new_link);
}
