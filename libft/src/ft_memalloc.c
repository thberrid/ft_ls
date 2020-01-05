/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:00:12 by thberrid          #+#    #+#             */
/*   Updated: 2019/04/19 19:23:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memalloc(size_t size)
{
	void	*new_str;

	new_str = malloc(sizeof(char) * size);
	if (new_str)
		ft_bzero(new_str, size);
	return (new_str);
}
