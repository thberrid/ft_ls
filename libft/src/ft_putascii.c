/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:06:36 by thberrid          #+#    #+#             */
/*   Updated: 2019/06/02 16:19:41 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putascii(void *ptr, size_t len)
{
	size_t			i;
	unsigned char	c;

	i = 0;
	while (i < len)
	{
		c = ((unsigned char *)ptr)[i];
		if (!ft_isprint(c))
			c = '.';
		write(1, &c, 1);
		i += 1;
	}
}
