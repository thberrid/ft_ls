/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_browse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:26:26 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 22:26:35 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_dlist		*dlist_search
	(t_dlist *new_elemnt, t_hlist *main, int (*f)(t_dlist *, t_dlist *))
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
