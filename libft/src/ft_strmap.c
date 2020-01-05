/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:13:21 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/20 15:37:13 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*new_str;
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen(s);
	new_str = ft_strnew(len);
	if (new_str)
	{
		i = 0;
		while (i < len)
		{
			new_str[i] = f(s[i]);
			i += 1;
		}
	}
	return (new_str);
}
