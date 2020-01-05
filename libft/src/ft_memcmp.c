/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 22:43:19 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/19 17:23:12 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		delta;

	delta = 0;
	i = 0;
	while (i < n)
	{
		delta = (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
		if (delta)
			return (delta);
		i += 1;
	}
	return (0);
}
