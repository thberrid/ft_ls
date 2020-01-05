/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:26:29 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/20 14:51:02 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *h, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*needle))
		return ((char *)h);
	i = 0;
	j = 0;
	while (h[i] && i < len)
	{
		j = 0;
		if (h[i] == needle[j])
		{
			while (i + j < len && h[i + j] && h[i + j] == needle[j])
			{
				j += 1;
				if (!(needle[j]))
					return ((char *)h + i);
			}
		}
		i += 1;
	}
	return (NULL);
}
