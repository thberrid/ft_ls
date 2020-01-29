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
	ft_memdel((void **)&filedata->lstat);
	ft_memdel((void **)&filedata->stat);
	if (filedata->dirent)
		ft_memdel((void **)&filedata->dirent);
	ft_memdel((void **)&filedata->path);
	ft_memdel((void **)&filedata);
	ft_memdel((void **)&lst);
}

size_t		filedata_get_total(t_dlist *this)
{
	t_filedata *filedata;

	filedata = (t_filedata *)this->content;
	return (filedata->lstat->st_blocks);
}

int			filedata_set_stat
	(t_filedata *filedata, t_dirent *dirent, char *root_path)
{
	if (!(filedata->lstat = ft_memalloc(sizeof(t_stat))))
		return (-1);
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
	if (lstat(filedata->path, filedata->lstat) && dirent)
		file_openfail_print(filedata);
	if (stat(filedata->path, filedata->stat) && dirent)
		file_openfail_print(filedata);
	return (0);
}
