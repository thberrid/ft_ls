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
	new->content_size = size;
	return (new);
}

void		dlist_init(t_dlist *lst, t_hlist *main)
{
	main->head = lst;
	main->tail = lst;
}

void		dlist_push(t_dlist *new_elemnt, t_hlist *handler)
{
	handler_update(handler, new_elemnt);
	if (!handler->tail)
		dlist_init(new_elemnt, handler);
	else
	{
		new_elemnt->next = NULL;
		new_elemnt->prev = handler->tail;
		handler->tail->next = new_elemnt;
		handler->tail = new_elemnt;
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

void		dlist_insert_before
	(t_dlist *new_elemnt, t_dlist *ref, t_hlist *handler)
{
	t_dlist *previous;

	if (!ref)
	{
		dlist_push(new_elemnt, handler);
		return ;
	}
	previous = ref->prev;
	if (previous)
		previous->next = new_elemnt;
	handler_update(handler, new_elemnt);
	new_elemnt->prev = previous;
	new_elemnt->next = ref;
	ref->prev = new_elemnt;
	if (handler->head == ref)
		handler->head = new_elemnt;
}
