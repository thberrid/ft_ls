/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 00:25:37 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/07 00:25:51 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*path_concat(char *path1, char *path2)
{
	char	*slash;
	char	*new_path;
	char	*buf;

	if (!(slash = ft_strdup("/")))
		return (NULL);
	if (!(buf = ft_strjoin(path1, slash)))
	{
		ft_strdel(&slash);
		return (NULL);
	}
	if (!(new_path = ft_strjoin(buf, path2)))
	{
		ft_strdel(&slash);
		ft_strdel(&buf);
		return (NULL);
	}
	ft_strdel(&buf);
	ft_strdel(&slash);
	return (new_path);
}

void	path_print(t_dlist *lst)
{
	t_filedata	*file;

	file = (t_filedata *)lst->content;
	ft_putstr(file->path);
	ft_putchar('\n');
}

void	pathroot_print(t_dlist *this)
{
	char	*last_slash;
	char	*pathroot;
	size_t	len;

	pathroot = ((t_filedata *)this->content)->path;
	last_slash = ft_strrchr(pathroot, '/');
	if (last_slash)
		len = last_slash - pathroot;
	else
		len = ft_strlen(pathroot);	
	ft_putnstr(pathroot, len);
	ft_putendl(":");
}

int		path_add(char *name, t_hlist *operands, t_options *options)
{
	t_dlist		*newlst;
	t_filedata	newfile;

	ft_bzero(&newfile, sizeof(t_filedata));
	if ((newfile.path = ft_strdup(name)) == 0)
		return (-1);
	if (filedata_set_stat(&newfile, NULL, NULL))
		return (1);
	if ((newlst = dlist_create(&newfile, sizeof(t_filedata))) == 0)
		return (-1);
	dlist_insert_before(newlst, dlist_search(newlst, operands, options->sort_f), operands);
	return (0);
}
