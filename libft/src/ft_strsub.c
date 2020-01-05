/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 20:10:18 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/19 20:25:18 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t size)
{
	char	*new_sub;

	new_sub = ft_strnew(size);
	if (new_sub)
		ft_strncpy(new_sub, s + start, size);
	return (new_sub);
}
