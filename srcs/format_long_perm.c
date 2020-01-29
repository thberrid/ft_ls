/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_long_perm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:11:45 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 22:11:52 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	file_extend_attr_print(t_filedata *filedata)
{
	if (listxattr(filedata->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putchar('@');
	else
		ft_putchar(' ');
	ft_putchar(' ');
}

void	file_type_print(t_stat *filestat)
{
	int						index;
	static const t_types	types[] = {
		{'l', S_IFLNK},
		{'c', S_IFCHR},
		{'s', S_IFSOCK},
		{'d', S_IFDIR},
		{'b', S_IFBLK},
		{'-', S_IFREG},
		{'p', S_IFIFO},
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

void	file_permission_print(t_stat *filestat, int level)
{
	int						index;
	static const t_types	types[] = {
		{'r', S_IREAD},
		{'w', S_IWRITE},
		{'x', S_IEXEC},
		{0, 0x0}
	};

	index = 0;
	while (types[index].symbol)
	{
		if (((types[index].mask >> level) & filestat->st_mode)
			== types[index].mask >> level)
			ft_putchar(types[index].symbol);
		else
			ft_putchar('-');
		index += 1;
	}
}

void	file_type_permission_print_all(t_filedata *filedata)
{
	file_type_print(filedata->lstat);
	file_permission_print(filedata->lstat, USR);
	file_permission_print(filedata->lstat, GRP);
	file_permission_print(filedata->lstat, OTHR);
	file_extend_attr_print(filedata);
}
