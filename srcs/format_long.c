/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_long_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:25:38 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 16:25:59 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	file_type_print(t_stat *filestat)
{
	int						index;
	static const t_types	types[] =
	{
		{'c', __S_IFCHR},
		{'d', __S_IFDIR},
		{'b', __S_IFBLK},
		{'-', __S_IFREG},
		{'l', __S_IFLNK},
		{'s', __S_IFSOCK},
		{'p', __S_IFIFO},
		{0, 0x0}
	};

	index = 0;
	while (types[index].symbol)
	{		
		if ((filestat->st_mode & types[index].mask) == types[index].mask)
		{
			ft_putchar(types[index].symbol);
			return ;
		}
		index += 1;
	}
	ft_putchar('?');
}

void	file_type_permission_print(t_stat *filestat, int level)
{
	int						index;
	static const t_types	types[] =
	{
		{'r', __S_IREAD},
		{'w', __S_IWRITE},
		{'x', __S_IEXEC},
		{0, 0x0}
	};

	index = 0;
	while (types[index].symbol)
	{
		if (((types[index].mask >> level) & filestat->st_mode) == types[index].mask >> level)
			ft_putchar(types[index].symbol);
		else
			ft_putchar('-');
		index += 1;
	}
}

void	format_long_print(t_dlist *elemnt, t_options *options)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)(elemnt->content);
	file_type_print(filedata->stat);
	file_type_permission_print(filedata->stat, USR);
	file_type_permission_print(filedata->stat, GRP);
	file_type_permission_print(filedata->stat, OTHR);
	ft_putchar(' ');
	ft_putstr("\t\t");
	if (filedata->dirent)
		ft_putnbr(filedata->dirent->d_type);
	else
		ft_putstr("no dirent");
	ft_putstr("\t\t");
	file_print_name(elemnt, options);
	ft_putstr("\n");
	if (file_is_last_elemnt(elemnt, options))
		ft_putchar('\n');
}