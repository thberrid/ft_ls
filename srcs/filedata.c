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

void		filedata_del_this(t_dlist *lst)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)(lst->content);
	ft_memdel((void **)&filedata->stat);
	if (filedata->dirent)
		ft_memdel((void **)&filedata->dirent);
	ft_memdel((void **)&filedata->path);
	ft_memdel((void **)&filedata);
	ft_memdel((void **)&lst);
}

int			filedata_open_this(t_dlist *this, t_options *options)
{
	t_hlist		files;
	int			retrn;
	DIR			*dir_open;
	t_filedata	*root_data;

	root_data = ((t_filedata *)this->content);
	if (!(dir_open = opendir(root_data->path)))
	{
		file_openfail_print(root_data);
		return (0);
	}
	ft_bzero(&files, sizeof(t_hlist));
	if ((filedata_readdir(dir_open, &files, this, options)))
		return (1);
	closedir(dir_open);
	retrn = core_loop(&files, options);
	dlist_foreach(&files, &filedata_del_this);
	return (retrn);
}

int			filedata_print_this(t_dlist *this, t_options *options)
{
	t_filedata	*filedata;

	(void)options;
	filedata = (t_filedata *)(this->content);
	ft_putnbr(filedata->stat->st_mode);
	ft_putstr("\t\t");
	if (filedata->dirent)
		ft_putnbr(filedata->dirent->d_type);
	else
		ft_putstr("no dirent");
	ft_putstr("\t\t");
	ft_putstr(filedata->path);
	ft_putstr("\n");
	return (0);
}

int			filedata_set_stat(t_filedata *filedata, t_dirent *dirent, char *root_path)
{
	if (!(filedata->stat = ft_memalloc(sizeof(t_stat))))
		return (-1);
	if (dirent)
	{
		if (!(filedata->path = path_concat(root_path, dirent->d_name)))
			return (-1);
		if (!(filedata->dirent = ft_memalloc(sizeof(t_dirent))))
			return (-1);
		ft_memcpy(filedata->dirent, dirent, sizeof(t_dirent));
	}
	if (lstat(filedata->path, filedata->stat))
		file_openfail_print(filedata);
	return (0);
}

int			filedata_readdir(DIR *dir_open, t_hlist *dest, t_dlist *root_file, t_options *options)
{
	t_dirent	*new_dirent;
	t_dlist		*new_lst;
	t_filedata	new_filedata;
	t_filedata	*root_data;

	(void)options;
	root_data = ((t_filedata *)root_file->content);
	while ((new_dirent = readdir(dir_open)))
	{
		ft_bzero(&new_filedata, sizeof(t_filedata));
		if (filedata_set_stat(&new_filedata, new_dirent, root_data->path))
			return (1);
		if (!(new_lst = dlist_create(&new_filedata, sizeof(t_filedata))))
			return (1);
		dlist_insert_before(new_lst, dlist_search(new_lst, dest, &path_sort_ascii), dest);
	}
	return (0);
}
