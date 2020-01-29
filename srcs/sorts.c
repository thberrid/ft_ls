/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 02:30:07 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/25 02:30:19 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		sort_last_mtime(t_dlist *l1, t_dlist *l2)
{
	t_timespec		file1_mtime;
	t_timespec		file2_mtime;
	__darwin_time_t	delta_sec;
	long			delta_nsec;

	file1_mtime = ((t_filedata *)l1->content)->lstat->st_mtimespec;
	file2_mtime = ((t_filedata *)l2->content)->lstat->st_mtimespec;
	delta_sec = file1_mtime.tv_sec - file2_mtime.tv_sec;
	if (delta_sec)
		return (((delta_sec < 0) ? 1 : 0));
	delta_nsec = file1_mtime.tv_nsec - file2_mtime.tv_nsec;
	if (delta_nsec)
		return (((delta_nsec < 0) ? 1 : 0));
	return (sort_path_ascii(l1, l2));
}

int		sort_path_ascii(t_dlist *l1, t_dlist *l2)
{
	return (ft_strcmp(((t_filedata *)l1->content)->path,
		((t_filedata *)l2->content)->path));
}
