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
	t_path	*path;

	path = (t_path *)lst->content;
	ft_putnbr(path->status);
	ft_putchar('\t');
	ft_putstr(path->name);
	ft_putchar('\n');
}

void	path_nonexist_print(t_dlist *lst)
{
	ft_putstr("ft_ls: ");
	ft_putstr(((t_path *)lst->content)->name);
	ft_putendl(" No such file o directory");
}

int		path_sort_ascii(t_dlist *l1, t_dlist *l2)
{
	return (ft_strcmp(((t_path *)l1->content)->name, ((t_path *)l2->content)->name));
}

int		path_add(char *name, t_hlist *operands)
{
	t_dlist		*lst;
	t_path		newpath;

	ft_bzero(&newpath, sizeof(t_path));
	if ((newpath.name = ft_strdup(name)) == 0)
		return (1);
	if ((lst = dlist_create(&newpath, sizeof(t_path))) == 0)
		return (1);
	dlist_insert_before(lst, dlist_search(lst, operands, &path_sort_ascii), operands);
	return (0);
}

int		path_set(int ac, char **av, t_options *options)
{
	int		i;

	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1])
	{
		i += 1;
		if (ft_strequ(av[i - 1], "--"))
			break ;
	}
	if (!(options->operands = ft_memalloc(sizeof(t_hlist))))
		return (1);
	if (!(options->inval_oper = ft_memalloc(sizeof(t_hlist))))
		return (1);
	while (i < ac)
	{
		if (path_add(av[i], file_exists(av[i]) ? options->operands : options->inval_oper))
			return (1);
		i += 1;
	}
	if (!options->operands->length && path_add("./", options->operands))
		return (1);
	dlist_foreach(options->inval_oper, &path_nonexist_print);
	return (0);
}
