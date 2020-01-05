/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:25:57 by thberrid          #+#    #+#             */
/*   Updated: 2018/11/20 19:50:13 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	ft_setinfos(int n, int *decimal, int *sign)
{
	*decimal = 1;
	*sign = 1;
	if (n < 0)
		*sign = -1;
	while (n / *decimal >= 10 || n / *decimal <= -10)
		*decimal *= 10;
}

void		ft_putnbr_fd(int n, int fd)
{
	int		decimal;
	int		sign;

	ft_setinfos(n, &decimal, &sign);
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (decimal > 0)
	{
		ft_putchar_fd((n / decimal * sign) + '0', fd);
		n %= decimal;
		decimal /= 10;
	}
}
