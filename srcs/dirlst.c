/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:25:38 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 16:25:59 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	dirlst_print(t_dlist *lst)
{
	t_dirlst	*dirlst;

	dirlst = (t_dirlst *)(lst->content);
	ft_putstr(dirlst->dirent->d_name);
	ft_putstr("\t\t");
	ft_putnbr(dirlst->dirstat->st_mode);
	ft_putchar('\n');
}

void	dirlist_del(t_dlist *lst)
{
	t_dirlst *dirlst;

	dirlst = (t_dirlst *)(lst->content);
	ft_memdel((void **)&dirlst->dirstat);
	ft_memdel((void **)&dirlst);
	ft_memdel((void **)&lst);
}
