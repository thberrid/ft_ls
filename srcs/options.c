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
	ft_bzero(options, sizeof(t_options));
	if (ac < 2)
		options->path = ft_strdup(".");
	else
		options->path = ft_strdup(av[1]);
	return (0);
}

void	options_free(t_options *options)
{
	ft_strdel(&options->path);
}
