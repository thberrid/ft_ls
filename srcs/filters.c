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

int			file_exists(char *name)
{
	t_stat		buf;

	ft_bzero(&buf, sizeof(t_stat));
	if ((lstat(name, &buf)) == 0)
		return (1);
	return (0);
}

int			file_is_fist_elemnt(t_dlist *elemnt, t_options *options)
{
	if (!flag_is_on(options->flags_lower, FLAG_R) && !elemnt->prev)
		return (1);
	if (flag_is_on(options->flags_lower, FLAG_R) && !elemnt->next)
		return (1);
	if (!((t_filedata *)elemnt->content)->dirent)
		return (1);
	return (0);
}

int			file_is_last_elemnt(t_dlist *elemnt, t_options *options)
{
	if (!flag_is_on(options->flags_lower, FLAG_R) && !elemnt->next)
		return (1);
	if (flag_is_on(options->flags_lower, FLAG_R) && !elemnt->prev)
		return (1);
	return (0);
}

/*
** !dirent && is_dir: 0
** if !flag(options.R) || (flag(options.R) && !dir)
*/

int		file_is_dotlink(t_dlist *file)
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

	if (!flag_is_on(options->flags_lower, FLAG_A))
		if (file_is_hidden(file))
			return (0);
	filedata = (t_filedata *)file->content;
	/*
	if ((filedata->stat
		&& file_isdir(filedata->stat))
		|| (filter_ishidden(file, options)))
		return (0);
	if (!flag_is_on(options->flags_upper, FLAG_R)
		|| (flag_is_on(options->flags_upper, FLAG_R)
			&& !file_isdir(filedata->stat)))
		return (1);
	*/
	return (1);
}

/*
** !dirent means core_loop is working on operands
*/

int		filter_recursion_dir(t_dlist *file, t_options *options)
{
	t_filedata *filedata;

	filedata = (t_filedata *)file->content;
	if (!flag_is_on(options->flags_lower, FLAG_A))
		if (file_is_hidden(file))
			return (0);
	if ((file_is_dir(filedata->stat) && !file_is_dotlink(file) && flag_is_on(options->flags_upper, FLAG_R))
		|| (file_is_dir(filedata->stat) && !((t_filedata *)file->content)->dirent))
		return (1);

/*
	if (!filedata->dirent)
		return (1);
	if (file_is_dotlink(file))
		return (0);
	if (!((t_filedata *)file->content)->dirent)
		return (1);
	if (!flag_is_on(options->flags_upper, FLAG_R))
		return (0);
	if (!((t_filedata *)file->content)->dirent
		|| (flag_is_on(options->flags_upper, FLAG_R)
			&& file_isdir(((t_filedata *)file->content)->stat))
		|| (flag_is_on(options->flags_upper, FLAG_R) && !((t_filedata *)file->content)->dirent))
		return (1);
	*/
	return (0);
}