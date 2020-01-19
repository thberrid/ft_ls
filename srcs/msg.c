/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 08:15:28 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/15 08:15:30 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	file_openfail_print(t_filedata *filedata)
{
	ft_putstr("ft_ls: ");
	ft_putstr(filedata->path);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

void	file_unexistent_print(t_dlist *lst)
{
	ft_putstr("ft_ls: ");
	ft_putstr(((t_filedata *)lst->content)->path);
	ft_putendl(": No such file or directory");
}

int		print_usage_and_quit(char invalid_char)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(invalid_char);
	ft_putchar('\n');
	ft_putstr("usage: ./ft_ls [-");
	ft_putstr(FLAGS_ALLOWD);
	ft_putendl("] [file ...]");
	return (1);
}
