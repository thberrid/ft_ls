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

void		dlist_insert_before(t_dlist *new_elemnt, t_dlist *ref, t_hlist *handler)
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

t_dlist		*dlist_search(t_dlist *new_elemnt, t_hlist *main, int (*f)(t_dlist *, t_dlist *))
{
	t_dlist	*this;

	this = main->head;
	while (this)
	{
		if (f(new_elemnt, this) <= 0)
			return (this);
		this = this->next;
	}
	return (this);
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

t_dlist		*dlist_next_or_prev(t_dlist *file, t_options *options)
{
	if (flag_is_on(options->flags_lower, FLAG_R))
		return (file->prev);
	return (file->next);
}

t_dlist		*dlist_head_or_tail(t_hlist *files, t_options *options)
{
	if (flag_is_on(options->flags_lower, FLAG_R))
		return (files->tail);
	return (files->head);
}

int			dlist_filter(t_hlist *handler_files, t_options *options, 
				int (*cond)(t_hlist *, t_dlist *, t_options *),
				int (*f)(t_dlist *, t_options *))
{
	t_dlist		*file;

	file = dlist_head_or_tail(handler_files, options);
	while (file)
	{
		if (cond(handler_files, file, options))
			if (f(file, options))
				return (1);
		file = dlist_next_or_prev(file, options);
	}
	return (0);
}

int			dlist_map(t_hlist *dest, t_hlist *src, void *options,
			int (*f)(t_hlist*, t_dlist*, void *options))
{
	t_dlist	*this;

	this = src->head;
	while (this)
	{
		if (f(dest, this, options))
			return (1);
		this = this->next;
	}
	return (0);
}
