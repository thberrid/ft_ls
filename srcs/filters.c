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

int			filter_ishidden(t_dlist *lst, t_options *options)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)lst->content;
	if (filedata->dirent->d_name[0] == '.' && !flag_is_on(options, FLAG_LOWER, FLAG_A))
		return (1);
	return (0);
}
