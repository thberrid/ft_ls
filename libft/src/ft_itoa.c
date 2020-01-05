/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:35:03 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/19 15:50:55 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	ft_setinfos(int n, int *decimal, size_t *size, int *sign)
{
	*size = 1;
	*decimal = 1;
	while ((n / *decimal >= 10) || (n / *decimal <= -10))
	{
		*decimal *= 10;
		*size += 1;
	}
	*sign = 1;
	if (n < 0)
	{
		*sign = -1;
		*size += 1;
	}
}

char		*ft_itoa(int n)
{
	char	*new_str;
	size_t	size;
	size_t	i;
	int		sign;
	int		decimal;

	ft_setinfos(n, &decimal, &size, &sign);
	new_str = ft_strnew(size);
	if (new_str)
	{
		i = 0;
		new_str[0] = '-';
		if (n < 0)
			i += 1;
		while (i < size)
		{
			new_str[i] = (n / decimal * sign) + '0';
			n %= decimal;
			decimal /= 10;
			i += 1;
		}
	}
	return (new_str);
}
