/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   total.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:44:55 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/22 06:45:09 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	total_print(t_hlist *handler, t_options *options)
{
	t_hcontent	*hcontent;

	(void)options;
	hcontent = ((t_hcontent *)handler->content);
	ft_putstr("total ");
	ft_putnbr(hcontent->total);
	ft_putchar('\n');
}