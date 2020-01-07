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

void	path_print(t_dlist *lst)
{
	t_path	*path;

	path = (t_path *)lst->content;
	ft_putnbr(path->status);
	ft_putchar('\t');
	ft_putstr(path->name);
	ft_putchar('\n');
}

int		status_set(char *name, t_path *path)
{
	t_stat		buf;

	ft_bzero(&buf, sizeof(t_stat));
	if ((lstat(name, &buf)) == 0)
		path->status = 1;
	else
	{
		ft_putstr("ft_ls: ");
		ft_putstr(name);
		ft_putendl(" No such file o directory");
	}
	return (0);
}

int		path_add(char *name, t_options *options)
{
	t_dlist		*lst;
	t_path		newpath;

	ft_bzero(&newpath, sizeof(t_path));
	if ((newpath.name = ft_strdup(name)) == 0)
		return (1);
	if (status_set(name, &newpath))
		return (1);
	if ((lst = dlist_create(&newpath, sizeof(t_path))) == 0)
		return (1);
	dlist_push(lst, options->paths);
	return (0);
}

int		path_set(int ac, char **av, t_options *options)
{
	int		i;

	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] && av[i][1] != '-')
		i += 1;
	if (!(options->paths = ft_memalloc(sizeof(t_options))))
		return (1);
	while (i < ac)
	{
		if (path_add(av[i], options))
			return (1);
		i += 1;
	}
	if (ac < 2 && path_add("./", options))
		return (1);
	return (0);
}