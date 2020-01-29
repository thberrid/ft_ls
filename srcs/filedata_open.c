/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedata_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:43:46 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 21:43:58 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int			filedata_readdir
	(DIR *dir_open, t_hlist *dest, t_dlist *root_file, t_options *options)
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
		if (!flag_is_on(options->flags_lower, FLAG_A)
			&& new_dirent->d_name[0] == '.')
			continue ;
		if (filedata_set_stat(&new_filedata, new_dirent, root_data->path))
			return (1);
		if (!(new_lst = dlist_create(&new_filedata, sizeof(t_filedata))))
			return (1);
		dlist_insert_before(new_lst,
			dlist_search(new_lst, dest, options->sort_f), dest);
	}
	return (0);
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
	if (!(files.content = ft_memalloc(sizeof(t_hcontent))))
		return (1);
	if ((filedata_readdir(dir_open, &files, this, options)))
		return (1);
	closedir(dir_open);
	retrn = filelist_header_print(&files, this, root_data, options);
	return (retrn);
}
