/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 04:21:27 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/06 04:21:30 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	flags_add(char new, t_options *options)
{
	if (!ft_ischarset(new, FLAGS_ALLOWD))
		return (1);
	if (ft_islower(new))
		options->flags_lower |= 1 << (new - 'a');
	else
		options->flags_upper |= 1 << (new - 'A');
	return (0);
}

int			flag_is_on(unsigned int flags_available, unsigned int flag_code)
{
	if (((flags_available ^ (1 << flag_code)) < flags_available))
		return (1);
	return (0);
}

char		flags_set(int ac, char **av, t_options *options)
{
	int		i;
	int		j;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		j = 1;
		if (av[i][1] == '-' && ft_strlen(av[i]) > 2)
			return (av[i][1]);
		while (av[i][j])
		{
			if (flags_add(av[i][j], options))
				return (av[i][j]);
			j += 1;
		}
		i += 1;
	}
	return (0);
}
