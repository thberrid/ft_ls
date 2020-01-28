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
	char	*filename;

	if (errno == ELOOP)
		return
	ft_putendl_fd(filedata->path, 2);
	ft_putstr_fd("ft_ls: ", 2);
	filename = ft_strrchr(filedata->path, '/');
	if (filename)
		filename += 1;
	else
		filename = filedata->path;
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	file_unexistent_print(t_dlist *lst)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(((t_filedata *)lst->content)->path, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	print_usage_and_quit(char invalid_char)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(invalid_char, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ./ft_ls [-", 2);
	ft_putstr_fd(FLAGS_ALLOWD, 2);
	ft_putendl_fd("] [file ...]", 2);
}
