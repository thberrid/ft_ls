/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:53:21 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/30 15:53:29 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	if (len)
	{
		dest = ft_strncpy(dest, src, len);
		dest[len] = 0;
	}
	return (dest);
}
