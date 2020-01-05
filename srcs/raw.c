/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 08:42:20 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 08:44:14 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void			raw_free(char **raw)
{
	int		i;

	i = 0;
	while (raw[i])
	{
		ft_memdel((void **)&raw[i]);
		i += 1;
	}
	ft_memdel((void **)&raw);
}

unsigned int	raw_len(char **raw)
{
	unsigned int	i;

	i = 0;
	while (raw && raw[i] && raw[i][0])
		i += 1;
	return (i);
}
