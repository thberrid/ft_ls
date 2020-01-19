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

int			file_isdir(t_stat *stat)
{
	if (S_ISDIR(stat->st_mode))
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

int			filter_ishidden(t_dlist *lst, t_options *options)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)lst->content;
	if (filedata->dirent->d_name[0] == '.'
		&& !flag_is_on(options->flags_lower, FLAG_A))
		return (1);
	return (0);
}

/*
** !dirent && is_dir: 0
** if !flag(options.R) || (flag(options.R) && !dir)
*/

int		is_dotlink(t_dlist *file)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)file->content;
	if (filedata->dirent)
		if (ft_strequ(filedata->dirent->d_name, ".") || ft_strequ(filedata->dirent->d_name, ".."))
			return (1);
	if (ft_strequ(filedata->path, ".") || ft_strequ(filedata->path, ".."))
		return (1);
	return (0);
}

int		filter_recursion_file(t_dlist *file, t_options *options)
{
	t_filedata	*filedata;

	if (is_dotlink(file))
		return (1);
	filedata = (t_filedata *)file->content;
	if ((filedata->stat
		&& file_isdir(filedata->stat))
		|| (filter_ishidden(file, options)))
		return (0);
	if (!flag_is_on(options->flags_upper, FLAG_R)
		|| (flag_is_on(options->flags_upper, FLAG_R)
			&& !file_isdir(filedata->stat)))
		return (1);
	return (0);
}

/*
** if (flag(options.R) || !this.dirent)
*/

int		filter_recursion_dir(t_dlist *file, t_options *options)
{
	t_filedata *filedata;

	filedata = (t_filedata *)file->content;
	if (is_dotlink(file))
		return (0);
	if (!((t_filedata *)file->content)->dirent
		|| (flag_is_on(options->flags_upper, FLAG_R)
			&& file_isdir(((t_filedata *)file->content)->stat))
		|| (flag_is_on(options->flags_upper, FLAG_R) && !((t_filedata *)file->content)->dirent))
		return (1);
	return (0);
}
