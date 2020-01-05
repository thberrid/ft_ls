/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 20:58:30 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/30 15:47:54 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	if (dest_len < size)
	{
		i = 0;
		while (src[i] && i < (size - dest_len - 1))
		{
			dest[dest_len + i] = src[i];
			i += 1;
		}
		dest[dest_len + i] = 0;
		return (dest_len + ft_strlen(src));
	}
	return (ft_strlen(src) + size);
}
