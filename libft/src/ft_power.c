/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 17:50:37 by thberrid          #+#    #+#             */
/*   Updated: 2018/12/16 16:32:39 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_power(int nb, int power)
{
	int		i;
	int		base;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	base = nb;
	i = 1;
	while (i < power)
	{
		nb *= base;
		i += 1;
	}
	return (nb);
}
