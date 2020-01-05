/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 21:17:04 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/19 20:22:47 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		ft_istrim(char c)
{
	if (c == 32 || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	size_t	len;
	char	*new_str;

	while (ft_istrim(*s))
		s += 1;
	len = ft_strlen(s);
	while (len > 0 && ft_istrim(s[len - 1]))
		len -= 1;
	new_str = ft_strsub(s, 0, len);
	return (new_str);
}
