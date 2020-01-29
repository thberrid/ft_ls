/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:26:49 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/07 16:26:52 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int			link_is_open(t_dlist *file, t_options *options)
{
	t_filedata	*filedata;
	char		*filename;

	(void)options;
	filedata = (t_filedata *)file->content;
	filename = filedata->path;
	if (S_ISLNK(filedata->lstat->st_mode)
		&& filename[ft_strlen(filename) - 1] == '/')
		return (1);
	return (0);
}

int			filter_printfile
	(t_hlist *handler, t_dlist *file, t_options *options)
{
	t_filedata	*filedata;

	(void)handler;
	filedata = (t_filedata *)file->content;
	if (!flag_is_on(options->flags_lower, FLAG_A))
		if (file_is_hidden(file))
			return (0);
	if (flag_is_on(options->flags_lower, FLAG_L)
		&& S_ISLNK(filedata->lstat->st_mode) && !link_is_open(file, options))
		return (1);
	if (!((t_filedata *)file->content)->dirent && file_is_dir(filedata->stat))
		return (0);
	return (1);
}

/*
** nb : (!dirent) means `operands`
** (the data was caught without open/readir)
*/

int			filter_openfile(t_hlist *handler, t_dlist *file, t_options *options)
{
	t_filedata *filedata;

	(void)handler;
	filedata = (t_filedata *)file->content;
	if (!flag_is_on(options->flags_lower, FLAG_A))
		if (file_is_hidden(file))
			return (0);
	if (flag_is_on(options->flags_lower, FLAG_L)
		&& S_ISLNK(filedata->lstat->st_mode) && !link_is_open(file, options))
		return (0);
	if ((file_is_dir(filedata->stat) && !file_is_dotlink(file)
		&& flag_is_on(options->flags_upper, FLAG_R))
		|| (file_is_dir(filedata->stat)
		&& !((t_filedata *)file->content)->dirent))
		return (1);
	return (0);
}
