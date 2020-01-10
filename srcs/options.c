/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:35:38 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 11:35:40 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int		print_usage_and_quit(char invalid_char)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(invalid_char);
	ft_putchar('\n');
	ft_putstr("usage: ./ft_ls [-");
	ft_putstr(FLAGS_ALLOWD);
	ft_putendl("] [file ...]");
	return (1);
}

static void		options_print(t_options *options)
{
	ft_putendl(DEBUG_TAG_OPEN);
	ft_putendl("- flags: ");
	print_memory(&options->flags_lower, sizeof(options->flags_lower));
	print_memory(&options->flags_upper, sizeof(options->flags_upper));
	ft_putchar('\n');
	ft_putstr("- path\nlen: ");
	ft_putnbr(options->operands->length);
	ft_putchar('\n');
	if (options->operands->length)
		ft_putendl("status\tname");
	dlist_foreach(options->operands, &path_print);
	ft_putendl(DEBUG_TAG_CLOSE);
}

int				options_set(int ac, char **av, t_options *options)
{
	int			retrn;

	retrn = 0;
	ft_bzero(options, sizeof(t_options));
	if (ac > 1 && av[1][0] == '-' && av[1][1] != '-')
		if ((retrn = flags_set(ac, av, options)))
			return (print_usage_and_quit(retrn));
	if (path_set(ac, av, options))
		return (1);
	if (DEBUG_MODE)
		options_print(options);
	return (0);
}

void			options_del(t_dlist *lst)
{
	t_path	*path;

	path = (t_path *)lst->content;
	ft_strdel(&path->name);
	ft_memdel((void **)&path);
	ft_memdel((void **)&lst);
}
