/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:53:03 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 21:53:18 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int			file_is_x(t_stat *filestat)
{
	if ((filestat->st_mode & S_IEXEC) == S_IEXEC)
		return (1);
	return (0);
}

int			file_is_dir(t_stat *stat)
{
	if (S_ISDIR(stat->st_mode))
		return (1);
	return (0);
}

int			file_is_hidden(t_dlist *file)
{
	t_filedata	*filedata;
	char		*last_slash;

	filedata = (t_filedata *)file->content;
	if (filedata->dirent)
	{
		if (filedata->dirent->d_name[0] == '.')
			return (1);
	}
	else
	{
		last_slash = ft_strrchr(filedata->path, '/');
		if (last_slash && *(last_slash + 1) == '.')
			return (1);
	}
	return (0);
}

int			file_is_dotlink(t_dlist *file)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)file->content;
	if (filedata->dirent)
		if (ft_strequ(filedata->dirent->d_name, ".")
			|| ft_strequ(filedata->dirent->d_name, ".."))
			return (1);
	if (ft_strequ(filedata->path, ".") || ft_strequ(filedata->path, ".."))
		return (1);
	return (0);
}

int			file_exists(char *name)
{
	t_stat		buf;

	ft_bzero(&buf, sizeof(t_stat));
	if ((lstat(name, &buf)) == 0)
		return (1);
	return (0);
}
