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
		{'c', S_IFCHR},
		{'d', S_IFDIR},
		{'b', S_IFBLK},
		{'-', S_IFREG},
		{'l', S_IFLNK},
		{'s', S_IFSOCK},
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
	static const t_types	types[] =
	{
		{'r', S_IREAD},
		{'w', S_IWRITE},
		{'x', S_IEXEC},
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

void	file_nbrlinks_print(t_stat *filestat)
{
	ft_putnbr(filestat->st_nlink);
	ft_putchar(' ');
}

void	file_type_permission_print_all(t_filedata *filedata)
{
	file_type_print(filedata->lstat);
	file_permission_print(filedata->lstat, USR);
	file_permission_print(filedata->lstat, GRP);
	file_permission_print(filedata->lstat, OTHR);
	ft_putchar(' ');
}

int		file_ownername_print(t_stat *filestat)
{
	t_passwd	*passwd;

	if (!(passwd = getpwuid(filestat->st_uid)))
		return (1);
	ft_putstr(passwd->pw_name);
	ft_putchar(' ');
	return (0);
}

int		file_groupname_print(t_stat *filestat)
{
	t_group	*group;

	if (!(group = getgrgid(filestat->st_gid)))
		return (1);
	ft_putstr(group->gr_name);
	ft_putchar(' ');
	return (0);
}

void	file_size_print(t_stat *filestat)
{
	ft_putnbr(filestat->st_size);
	ft_putchar(' ');
}

int		file_date_print(t_stat *filestat)
{
	char	*date;

	if (!(date = ctime((time_t *)(&filestat->st_mtimespec))))
		return (1);
	date[ft_strlen(date) - 2] = '\0';
	ft_putstr(date);
	ft_putchar(' ');
	return (0);
}

int		format_long_print(t_dlist *elemnt, t_options *options)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)(elemnt->content);
	file_type_permission_print_all(filedata);
	file_nbrlinks_print(filedata->lstat);
	if (file_ownername_print(filedata->lstat))
		return (1);
	if (file_groupname_print(filedata->lstat))
		return (1);
	file_size_print(filedata->lstat);
	if (file_date_print(filedata->lstat))
		return (1);
	file_print_name(elemnt, options);
	ft_putchar('\n');
//	if (file_is_last_elemnt(elemnt, options))
//		ft_putchar('\n');
	return (0);
}