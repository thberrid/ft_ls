/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:01:44 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 11:06:07 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
int		ls_root(t_options *options)
{
	t_hlist		main;
	int			retrn;

	retrn = 0;
	ft_bzero(&main, sizeof(t_hlist));
//	if ((retrn = dir_get(options, &main)))
//		return (1);
//	dlist_foreach(&main, &dirlst_print);
	dlist_foreach(&main, &dirlist_del);
	return (0);
}
*/
int		main(int ac, char **av)
{
	t_options	options;
	int			retrn;

	if ((retrn = options_set(ac, av, &options)))
		return (0);
//	if ((retrn = ls_root(&options)))
//		ft_putendl(strerror(errno));
	dlist_foreach(options.paths, &options_del);
	return (0);
}
