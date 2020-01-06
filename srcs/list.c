/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 13:51:17 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 13:51:20 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_dlist		*dlist_create(void *content, size_t size)
{
	t_dlist	*new;

	if (!(new = ft_memalloc(sizeof(t_dlist))))
		return (NULL);
	if (!(new->content = ft_memalloc(size)))
	{
		ft_memdel((void **)&new);
		return (NULL);
	}
	ft_memcpy(new->content, content, size);
	return (new);
}

void		dlist_init(t_dlist *lst, t_hlist *main)
{
	main->head = lst;
	main->tail = lst;
}

void		dlist_push(t_dlist *lst, t_hlist *main)
{
	main->len += 1;
	if (!main->tail)
		dlist_init(lst, main);
	else
	{
		lst->next = NULL;
		lst->prev = main->tail;
		main->tail->next = lst;
		main->tail = lst;
	}
}

void		dlist_unshift(t_dlist *lst, t_hlist *main)
{
	if (!main->tail)
		dlist_init(lst, main);
	else
	{
		lst->prev = NULL;
		lst->next = main->head;
		main->head->next = lst;
		main->head = lst;
	}
}

void		dlist_foreach(t_hlist *main, void (*f)(t_dlist *))
{
	t_dlist		*lst;
	t_dlist		*next;

	next = main->head;
	while (next)
	{
		lst = next;
		next = lst->next;
		f(lst);
	}
}
