/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_long_owners.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:14:57 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 22:20:48 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	file_nbrlinks_print(t_stat *filestat)
{
	ft_putnbr(filestat->st_nlink);
	ft_putchar('\t');
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
		ft_putchar(' ');
		date[ft_strlen(date) - 1] = '\0';
		ft_putstr(date + TIME_Y + ft_spacelen(date + TIME_Y));
	}
	ft_putchar(' ');
	return (0);
}

int		file_print_link(t_dlist *elemnt)
{
	t_filedata	*filedata;
	char		buff[PATH_MAX];

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
	return (0);
}
