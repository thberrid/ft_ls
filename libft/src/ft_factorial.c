/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:32:11 by thberrid          #+#    #+#             */
/*   Updated: 2018/12/16 16:31:37 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_factorial(int nb)
{
	int		i;
	int		factor;

	i = 1;
	factor = 1;
	if (nb >= 0 && nb < 13)
	{
		while (i <= nb)
		{
			factor *= i;
			i += 1;
		}
	}
	else
		return (0);
	return (factor);
}
