/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 12:51:30 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 12:51:33 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		dir_browse(t_options *options)
{
	DIR 		*dir_open;
	t_dirent	*dir_current;
	t_stat 		file;
	int			retrn;

	dir_open = opendir(options->path);
	while ((dir_current = readdir(dir_open)))
	{
		retrn = stat(dir_current->d_name, &file);
		ft_putendl(dir_current->d_name);
	}
	closedir(dir_open);
	return (0);
}

void	dir_free(t_dirent *dir)
{
	free(dir);
}