/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 08:58:22 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/02 08:58:26 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	pen_update_color(t_pixel *pen)
{
	color_decr(&pen->color, 1, RED);
	color_decr(&pen->color, 1, GREEN);
	color_decr(&pen->color, 1, BLUE);
}

void	pen_init(t_pixel *pen, t_pixel *start)
{
	ft_bzero(pen, sizeof(t_pixel));
	pen->x = start->x;
	pen->y = start->y;
	pen->color = start->color;
}
