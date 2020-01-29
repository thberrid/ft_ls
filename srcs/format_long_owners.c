/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_long_owners.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:14:57 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 22:15:07 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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
