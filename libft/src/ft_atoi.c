/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:46:31 by thberrid          #+#    #+#             */
/*   Updated: 2019/05/18 23:06:42 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nb;

	sign = 1;
	i = 0;
	nb = 0;
	while (*str && ft_isspace(*str))
		str += 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str += 1;
	while (*str && ft_isdigit(*str))
	{
		nb *= 10;
		nb += *(str + i) - '0';
		str += 1;
	}
	return (nb * sign);
}
