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

/*	moove_ptr(flag r, lst_this)
**		if (options.r)
**			list = list.prev
**		else
**			list = list.next
**
**	---
**
**	core_loop(list, options): 
**		foreach:
**			if !flag(options.R) || (flag(options.R) && !dir) || !!dirent
**				print
**				move_ptr(options.r, list.this)
**		if (flag(options.R) || !this.dirent)
**			foreach:
**				if dir
**					print
**					this->subfiles = open, readdir, close
**					core_loop(this->subfiles)
**				move_ptr(options.r, list.this)
*/

int		core_loop(t_hlist *files, t_options *options)
{
	if (dlist_filter(files, options, &filter_printfile, &filedata_print_this))
		return (1);
	if (dlist_filter(files, options,
		&filter_openfile, &filedata_open_this))
		return (1);
	return (0);
}

int		main(int ac, char **av)
{
	t_options	options;

	if (options_set(ac, av, &options))
		return (0);
	if (core_loop(options.operands, &options))
		ft_putendl(strerror(errno));
	options_del(&options);
	if (LEAKS_MODE)
		system("leaks ft_ls");
	return (0);
}
