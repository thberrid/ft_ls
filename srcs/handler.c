/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:49:46 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/22 06:49:49 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_hlist		*handler_create(t_hlist **handler)
{
	if (!(*handler = ft_memalloc(sizeof(t_hlist))))
		return (NULL);
	if (!((*handler)->content = ft_memalloc(sizeof(t_hcontent))))
		return (NULL);
	return (*handler);
}

void		handler_update(t_hlist *handler, t_dlist *new_elemnt)
{
	handler->length += 1;
//	ft_putstr("oops ");
//	ft_putnbr(filedata_get_total(new_elemnt));
//	ft_putendl("");
	((t_hcontent *)handler->content)->total += filedata_get_total(new_elemnt);
}
