/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedata_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:42:20 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/29 21:42:23 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		total_print(t_hlist *handler, t_options *options)
{
	t_hcontent	*hcontent;

	(void)options;
	hcontent = ((t_hcontent *)handler->content);
	ft_putstr("total ");
	ft_putnbr(hcontent->total);
	ft_putchar('\n');
}

int			filelist_header_print
	(t_hlist *files, t_dlist *this, t_filedata *root_data, t_options *options)
{
	t_dlist		*header;
	int			retrn;

	header = dlist_head_or_tail(files, options);
	if (file_is_dir(root_data->stat)
		&& ((file_is_single(this) && (options->operands_invalid->length
			|| root_data->dirent)) || (!file_is_single(this))))
		pathroot_print(this);
	if (!files->length)
	{
		ft_memdel((void **)&files->content);
		return (0);
	}
	if (file_is_first_elemnt(header, options)
		&& flag_is_on(options->flags_lower, FLAG_L)
		&& file_is_x(root_data->lstat))
		total_print(files, options);
	retrn = core_loop(files, options);
	dlist_foreach(files, &filedata_del_this);
	ft_memdel((void **)&files->content);
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
}

int			filedata_print_this(t_dlist *this, t_options *options)
{
	if (!((t_filedata *)this->content)->stat->st_mode &&
		flag_is_on(options->flags_lower, FLAG_L))
		return (0);
	if (flag_is_on(options->flags_lower, FLAG_L))
	{
		if (format_long_print(this, options))
			return (1);
	}
	else
		file_print_name(this, options);
	if (!flag_is_on(options->flags_lower, FLAG_L))
		ft_putchar(' ');
	if (file_is_last_elemnt(this, options))
		ft_putchar('\n');
	return (0);
}
