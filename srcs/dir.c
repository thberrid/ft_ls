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

static int	dirlst_set(t_dirlst *dest, t_dirent *src)
{
	if (!(dest->dirstat = ft_memalloc(sizeof(t_stat))))
		return (1);
	if (!(dest->dirent = ft_memalloc(sizeof(t_dirent))))
		return (1);
	ft_memcpy(dest->dirent, src, sizeof(t_dirent));
	return (0);
}

int			dir_get(t_options *options, t_hlist *main)
{
	DIR			*dir_open;
	t_dlist		*new;
	t_dirlst	dirlst;
	t_dirent	*this_dir;
	char		*path;

	if (!(dir_open = opendir(options->path)))
		return (1);
	ft_bzero(&dirlst, sizeof(t_dirlst));
	while ((this_dir = readdir(dir_open)))
	{
		if (dirlst_set(&dirlst, this_dir))
			return (1);
		path = ft_strjoin(options->path, dirlst.dirent->d_name);
		if (lstat(path, dirlst.dirstat))
			return (1);
		if (!(new = dlist_create(&dirlst, sizeof(t_dirlst))))
			return (1);
		dlist_push(new, main);
		ft_strdel(&path);
	}
	closedir(dir_open);
	return (0);
}
