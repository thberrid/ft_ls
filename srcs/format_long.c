/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_long_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 16:25:38 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 16:25:59 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	format_long_print(t_dlist *elemnt, t_options *options)
{
	t_filedata	*filedata;

	filedata = (t_filedata *)(elemnt->content);	
	ft_putnbr(filedata->stat->st_mode);
	ft_putstr("\t\t");
	if (filedata->dirent)
		ft_putnbr(filedata->dirent->d_type);
	else
		ft_putstr("no dirent");
	ft_putstr("\t\t");
	file_print_name(elemnt, options);
	ft_putstr("\n");
	if (file_is_last_elemnt(elemnt, options))
		ft_putchar('\n');
}