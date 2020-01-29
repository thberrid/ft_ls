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
	ft_putchar('\t');
}

void	file_type_permission_print_all(t_filedata *filedata)
{
	file_type_print(filedata->lstat);
	file_permission_print(filedata->lstat, USR);
	file_permission_print(filedata->lstat, GRP);
	file_permission_print(filedata->lstat, OTHR);
	file_extend_attr_print(filedata);
}

void	file_ownername_print(t_stat *filestat)
{
	t_passwd	*passwd;

	if (!(passwd = getpwuid(filestat->st_uid)))
		ft_putstr("no owner");
	else
		ft_putstr(passwd->pw_name);
	ft_putchar(' ');
}

void	file_groupname_print(t_stat *filestat)
{
	t_group	*group;

	if (!(group = getgrgid(filestat->st_gid)))
		ft_putstr("no group");
	else
		ft_putstr(group->gr_name);
	ft_putchar(' ');
}

void	file_size_print(t_stat *filestat)
{
	int		intlen;
	ft_putnbr(filestat->st_size);
	intlen = ft_intlen(filestat->st_size);
	if (intlen <= 4)
		ft_putchar('\t');
	ft_putchar('\t');
}

int		ft_spacelen(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i += 1;
	return (i);
}

int		file_date_print(t_stat *filestat)
{
	char	*date;
	time_t	now;
	time_t	*file_time;
	time_t	delta;

	file_time = (time_t *)(&filestat->st_mtimespec);
	now = time(NULL);
	delta = *file_time - now;
	if (delta < 0)
		delta *= -1;
	if (!(date = ctime(file_time)))
		return (1);
	ft_putnstr(date + 4, 7);
	if (delta < TIME_6_MONTHS)
		ft_putnstr(date + TIME_HM, TIME_HM_LEN);
	else
	{
	//	ft_putstr("ono ");
	//	ft_putendl(date);
		ft_putchar(' ');
		date[ft_strlen(date) - 1] = '\0';
		ft_putstr(date + TIME_Y + ft_spacelen(date + TIME_Y));
	}
	ft_putchar(' ');

//	date[ft_strlen(date) - 9] = '\0';
//	ft_putstr(date);
//	ft_putchar(' ');
	return (0);
}

int		file_print_link(t_dlist *elemnt)
{
	t_filedata	*filedata;
	char 		buff[PATH_MAX];

	filedata = (t_filedata *)(elemnt->content);
	if (S_ISLNK(filedata->lstat->st_mode))
	{
		ft_putstr(" -> ");
		ft_bzero(buff, sizeof(buff));
		if (readlink(filedata->path, buff, sizeof(buff) - 1) < 0)
			return (1);
		ft_putstr(buff);
	}
	return (0);
}

void	file_extend_attr_print(t_filedata *filedata)
{
	if (listxattr(filedata->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putchar('@');
	else
		ft_putchar(' ');
	ft_putchar(' ');
}

int		format_long_print(t_dlist *elemnt, t_options *options)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)(elemnt->content);
	file_type_permission_print_all(filedata);
	file_nbrlinks_print(filedata->lstat);
	file_ownername_print(filedata->stat);
	file_groupname_print(filedata->lstat);
	file_size_print(filedata->lstat);
	if (file_date_print(filedata->lstat))
		return (1);
	file_print_name(elemnt, options);
	file_print_link(elemnt);
	ft_putchar('\n');
//	if (file_is_last_elemnt(elemnt, options))
//		ft_putchar('\n');
	return (0);
}