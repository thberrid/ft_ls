/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:55:25 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 21:55:38 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int			file_is_single(t_dlist *elemnt)
{
	if (!elemnt->next && !elemnt->prev)
		return (1);
	return (0);
}

int			file_is_first_elemnt(t_dlist *elemnt, t_options *options)
{
	if (!elemnt)
		return (1);
	if (!flag_is_on(options->flags_lower, FLAG_R) && !elemnt->prev)
		return (1);
	if (flag_is_on(options->flags_lower, FLAG_R) && !elemnt->next)
		return (1);
	return (0);
}

int			file_is_last_elemnt(t_dlist *elemnt, t_options *options)
{
	if (!elemnt)
		return (1);
	if (!flag_is_on(options->flags_lower, FLAG_R) && !elemnt->next)
		return (1);
	if (flag_is_on(options->flags_lower, FLAG_R) && !elemnt->prev)
		return (1);
	return (0);
}
