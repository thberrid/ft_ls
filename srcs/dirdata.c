/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:25:38 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 16:25:59 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		dirlist_del(t_dlist *lst)
{
	t_dirdata	*dirdata;

	dirdata = (t_dirdata *)(lst->content);
	ft_memdel((void **)&dirdata->dirstat);
	ft_memdel((void **)&dirdata);
	ft_memdel((void **)&lst);
}

int			dirdata_print(t_hlist *paths, t_dlist *lst, t_options *options)
{
	t_dirdata	*dirdata;

	dirdata = (t_dirdata *)(lst->content);
	ft_putstr(dirdata->dirent->d_name);
	ft_putstr("\t");
	ft_putnbr(dirdata->dirstat->st_mode);
	ft_putchar('\n');
	if (0)
	{
		if (ls_root(options, paths))
			return (1);
	}
	return (0);
}

static int	dirdata_fill(t_dirdata *dirdata, t_dirent *dirent)
{
	char		*path;

	if (!(dirdata->dirent = ft_memalloc(sizeof(t_dirent))))
		return (1);
	ft_memcpy(dirdata->dirent, dirent, sizeof(t_dirent));
	if (!(dirdata->dirstat = ft_memalloc(sizeof(t_stat))))
		return (1);
	if (!(path = path_concat(dirdata->path->name, dirdata->dirent->d_name)))
		return (1);
	if (lstat(path, dirdata->dirstat))
		return (1);
	ft_strdel(&path);
	return (0);
}

int			dirdata_set(t_hlist *dest, t_dlist *lst, t_options *options)
{
	DIR			*dir_open;
	t_dirent	*new_dirent;
	t_dlist		*new_ls;
	t_dirdata	new_dirdata;

	(void)options;
	ft_bzero(&new_dirdata, sizeof(t_dirdata));
	new_dirdata.path = (t_path *)lst->content;
	if (new_dirdata.path->status == 0)
		return (0);
	if (!(dir_open = opendir(new_dirdata.path->name)))
		return (1);
	ft_putendl(new_dirdata.path->name);
	while ((new_dirent = readdir(dir_open)))
	{
		if (dirdata_fill(&new_dirdata, new_dirent))
			return (1);
		if (!(new_ls = dlist_create(&new_dirdata, sizeof(t_dirdata))))
			return (1);
		dlist_push(new_ls, dest);
	}
	closedir(dir_open);
	return (0);
}
