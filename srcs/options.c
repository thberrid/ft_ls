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

int				operands_set(int ac, char **av, t_options *options)
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
	if (!(options->operands_invalid = ft_memalloc(sizeof(t_hlist))))
		return (1);
	while (i < ac)
	{
		if (path_add(av[i], file_exists(av[i]) ? options->operands : options->operands_invalid) == -1)
			return (1);
		i += 1;
	}
	if (!options->operands->length && !options->operands_invalid->length && path_add(".", options->operands))
		return (1);
	dlist_foreach(options->operands_invalid, &file_unexistent_print);
	return (0);
}

static void		options_print(t_options *options)
{
	ft_putstr(DEBUG_BLUE);
	ft_putstr(DEBUG_TAG);
	ft_putendl("- flags: ");
	print_memory(&options->flags_lower, sizeof(options->flags_lower));
	print_memory(&options->flags_upper, sizeof(options->flags_upper));
	ft_putchar('\n');
	ft_putstr("- paths:\nlen: ");
	ft_putnbr(options->operands->length);
	ft_putstr("\n");
	dlist_foreach(options->operands, &path_print);
	ft_putstr(DEBUG_TAG);
	ft_putstr(DEBUG_GREY);
	ft_putstr("s.st_mode\td.d_type\tpath\n\n");
	ft_putstr(DEBUG_CLEAR);
}

int				options_set(int ac, char **av, t_options *options)
{
	int			retrn;

	retrn = 0;
	ft_bzero(options, sizeof(t_options));
	if (ac > 1 && av[1][0] == '-' && av[1][1] != '-')
	{
		if ((retrn = flags_set(ac, av, options)))
		{
			print_usage_and_quit(retrn);
			return (1);
		}
	}
	if (operands_set(ac, av, options))
		return (1);
	if (DEBUG_MODE)
		options_print(options);
	return (0);
}

void		options_del(t_options *options)
{
	dlist_foreach(options->operands, &filedata_del_this);
	dlist_foreach(options->operands_invalid, &filedata_del_this);
	ft_memdel((void **)&options->operands);
	ft_memdel((void **)&options->operands_invalid);
}
