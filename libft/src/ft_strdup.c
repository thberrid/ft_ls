/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:51:53 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/20 21:57:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(s);
	new_str = ft_strnew(len);
	if (new_str)
		ft_strncpy(new_str, s, len);
	return (new_str);
}
