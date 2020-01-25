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

int			filedata_open_this(t_dlist *this, t_options *options)
{
	t_hlist		files;
	int			retrn;
	DIR			*dir_open;
	t_filedata	*root_data;
	t_dlist		*header;

	root_data = ((t_filedata *)this->content);
	if (!(dir_open = opendir(root_data->path)))
	{
		file_openfail_print(root_data);
		return (0);
	}
	ft_bzero(&files, sizeof(t_hlist));
	if (!(files.content = ft_memalloc(sizeof(t_hcontent))))
		return (1);
	if ((filedata_readdir(dir_open, &files, this, options)))
		return (1);
	header = dlist_head_or_tail(&files, options);
//	if (file_is_first_elemnt(header, options))
//		ft_putchar('\n');
//	ft_putendl("?");
	if (file_is_first_elemnt(this, options) && (!file_is_single(this) || options->operands_invalid->length))
		pathroot_print(this);
	if (!files.length)
		return (0);
	if (file_is_first_elemnt(header, options) && flag_is_on(options->flags_lower, FLAG_L))
		total_print(&files, options);
	closedir(dir_open);
	// if one day u want to sort, thats sould be somewhere here approximatively
	retrn = core_loop(&files, options);
///	if (!file_is_last_elemnt(this, options))
///		ft_putchar('\n');
	dlist_foreach(&files, &filedata_del_this);
	ft_memdel((void **)&files.content);
	return (retrn);
}

void		file_print_name(t_dlist *elemnt, t_options *options)
{
	t_filedata	*filedata;

	(void)options;
	filedata = (t_filedata *)(elemnt->content);	
	if (filedata->dirent)
		ft_putstr(filedata->dirent->d_name);
	else
		ft_putstr(filedata->path);
	if (file_is_last_elemnt(elemnt, options))
		ft_putchar('\n');
	else
		ft_putchar(' ');
     
}

int			filedata_print_this(t_dlist *this, t_options *options)
{
	if (flag_is_on(options->flags_lower, FLAG_L))
	{
		if (format_long_print(this, options))
			return (1);
	}
	else
		file_print_name(this, options);
//	if (file_is_last_elemnt(this, options))
//		ft_putchar('\n');
	return (0);
}

int			filedata_set_stat(t_filedata *filedata, t_dirent *dirent, char *root_path)
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
		if (!flag_is_on(options->flags_lower, FLAG_A) && new_dirent->d_name[0] == '.')
			continue ;
		if (filedata_set_stat(&new_filedata, new_dirent, root_data->path))
			return (1);
		if (!(new_lst = dlist_create(&new_filedata, sizeof(t_filedata))))
			return (1);
		dlist_insert_before(new_lst, dlist_search(new_lst, dest, options->sort_f), dest);
	}
	return (0);
}
