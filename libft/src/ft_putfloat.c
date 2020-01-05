/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 02:22:48 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/20 02:26:32 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_decimal(float nbr, unsigned int decimal)
{
	unsigned int	i;
	int				int_part;

	i = 0;
	while (i < decimal)
	{
		nbr *= 10;
		int_part = (int)nbr;
		nbr -= int_part;
		i += 1;
	}
	return (int_part);
}

void		ft_putfloat(float nbr, int precision)
{
	int		i;
	int		int_part;

	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	int_part = (int)nbr;
	ft_putnbr(int_part);
	nbr -= int_part;
	if (precision)
		ft_putchar('.');
	i = 0;
	while (nbr && precision)
	{
		int_part = get_decimal(nbr, 1);
		if (precision == 1 && get_decimal(nbr, 2) >= 5 && int_part < 9)
			int_part += 1;
		ft_putnbr(int_part);
		nbr *= 10;
		nbr -= int_part;
		precision -= 1;
	}
}
