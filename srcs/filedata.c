/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:25:38 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 16:25:59 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		file_exists(char *name)
{
	t_stat		buf;

	ft_bzero(&buf, sizeof(t_stat));
	if ((lstat(name, &buf)) == 0)
		return (1);
	return (0);
}

void		filelist_del(t_dlist *lst)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)(lst->content);
	ft_memdel((void **)&filedata->filestat);
	ft_memdel((void **)&filedata->dirent);
	ft_memdel((void **)&filedata);
	ft_memdel((void **)&lst);
}

void		filedata_print_this(t_dlist *lst, t_options *options)
{
	t_filedata	*filedata;

//	if (options->paths->length > 1)
//		ft_putendl()
	(void)options;
	filedata = (t_filedata *)(lst->content);
	ft_putnbr(filedata->filestat->st_mode);
	ft_putstr("\t");
	ft_putnbr(filedata->dirent->d_type);
	ft_putstr("\t");
	ft_putstr(filedata->dirent->d_name);
	ft_putstr("\n");
	/*
	if (0)
	{
		if (ls_root(options, paths))
			return (1);
	}
	*/
}

void		filedata_print(t_hlist *main, t_options *options)
{
	t_dlist	*this;

	this = main->head;
	while (this)
	{
		if (filter_ishidden(this, options) == 0)
			filedata_print_this(this, options);
		this = this->next;
	}
}

static int	filedata_fill(t_filedata *filedata, t_dirent *dirent)
{
	char		*path;

	if (!(filedata->dirent = ft_memalloc(sizeof(t_dirent))))
		return (1);
	ft_memcpy(filedata->dirent, dirent, sizeof(t_dirent));
	if (!(filedata->filestat = ft_memalloc(sizeof(t_stat))))
		return (1);
	if (!(path = path_concat(filedata->paths->name, filedata->dirent->d_name)))
		return (1);
	if (lstat(path, filedata->filestat))
		return (1);
	ft_strdel(&path);
	return (0);
}

int			filedata_set(t_hlist *dest, t_dlist *lst, t_options *options)
{
	DIR			*dir_open;
	t_dirent	*new_dirent;
	t_dlist		*new_ls;
	t_filedata	new_filedata;

	(void)options;
	ft_bzero(&new_filedata, sizeof(t_filedata));
	new_filedata.paths = (t_path *)lst->content;
	if (new_filedata.paths->status == 0)
		return (0);
	if (!(dir_open = opendir(new_filedata.paths->name)))
		return (1);
	while ((new_dirent = readdir(dir_open)))
	{
		if (filedata_fill(&new_filedata, new_dirent))
			return (1);
		if (!(new_ls = dlist_create(&new_filedata, sizeof(t_filedata))))
			return (1);
		dlist_push(new_ls, dest);
	}
	closedir(dir_open);
	return (0);
}
