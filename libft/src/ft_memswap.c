/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:07:58 by thberrid          #+#    #+#             */
/*   Updated: 2019/04/14 16:28:01 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int			ft_memswap(void *addr_a, void *addr_b, size_t size)
{
	void	*tmp;

	if ((tmp = ft_memalloc(sizeof(char) * size)))
	{
		ft_memcpy(tmp, addr_a, size);
		ft_memcpy(addr_a, addr_b, size);
		ft_memcpy(addr_b, tmp, size);
		ft_memdel(&tmp);
		return (1);
	}
	return (0);
}
