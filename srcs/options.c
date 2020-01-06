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

int		options_set(int ac, char **av, t_options *options)
{
	int		retrn;

	retrn = 0;
	ft_bzero(options, sizeof(t_options));
	if (ac > 1 && av[1][0] == '-' && av[1][1] != '-')
		retrn = flags_set(ac, av, options);
//	if (ac < 2)
		options->path = ft_strdup("./");
//	else
//		options->path = ft_strjoin(av[1], "/");
	if (!options->path)
		return (1);
	return (0);
}

void	options_free(t_options *options)
{
	ft_strdel(&options->path);
}
