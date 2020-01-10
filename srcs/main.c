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

int		ls_root(t_options *options, t_hlist *paths)
{
	t_hlist		files;

	ft_bzero(&files, sizeof(t_hlist));
	if (dlist_map(&files, paths, options, (void *)&filedata_set))
		return (1);
	ft_putendl("\nmode\ttype\tname\n");
	filedata_print(&files, options);
	dlist_foreach(&files, &filelist_del);
	return (0);
}

int		main(int ac, char **av)
{
	t_options	options;
	int			retrn;

	if ((retrn = options_set(ac, av, &options)))
		return (0);
	if ((retrn = ls_root(&options, options.operands)))
		ft_putendl(strerror(errno));
	dlist_foreach(options.operands, &options_del);
	dlist_foreach(options.inval_oper, &options_del);
	ft_memdel((void **)&options.operands);
	return (0);
}
