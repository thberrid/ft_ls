/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 20:30:26 by thberrid          #+#    #+#             */
/*   Updated: 2019/05/30 10:24:48 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_join;

	new_join = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (new_join)
	{
		ft_strcpy(new_join, s1);
		ft_strcat(new_join, s2);
	}
	return (new_join);
}
