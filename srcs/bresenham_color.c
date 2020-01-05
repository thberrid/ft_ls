/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:21:41 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 14:05:37 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
**	red 	= step_color >> 8
**	green 	= step_color >> 16
*/

void	bresen_init_stepcolor(unsigned int delta_fast, t_pixel *pen,
	t_pixel *start, t_pixel *end)
{
	unsigned int	step_color;

	step_color = start->color ^ end->color;
	if ((step_color >> 8) && delta_fast)
		pen->step_red = (float)((unsigned char)(step_color >> 8)) / delta_fast;
	if ((step_color >> 16) && delta_fast)
		pen->step_green = (float)((unsigned char)(step_color >> 16))
			/ delta_fast;
}

void	bresen_increm_color(t_pixel *start, t_pixel *end, t_pixel *pen,
	unsigned int step_color)
{
	if (start->y >= end->y)
	{
		if ((char)(step_color >> 16))
			color_decr(&pen->color, (unsigned char)(pen->step_green), RED);
		if ((char)(step_color >> 8))
			color_incr(&pen->color, (unsigned char)(pen->step_red), GREEN);
	}
	else
	{
		if ((char)(step_color >> 16))
			color_incr(&pen->color, (unsigned char)(pen->step_green), RED);
		if ((char)(step_color >> 8))
			color_decr(&pen->color, (unsigned char)(pen->step_red), GREEN);
	}
}

void	bresen_update_color(t_pixel *pen, t_pixel *start, t_pixel *end,
	unsigned int d_fast)
{
	unsigned int step_color;

	step_color = pen->color ^ end->color;
	if (pen->step_green < 1 && d_fast)
		pen->step_green += (float)((unsigned char)(step_color >> 16)) / d_fast;
	if (pen->step_red < 1 && d_fast)
		pen->step_red += (float)((unsigned char)(step_color >> 8)) / d_fast;
	bresen_increm_color(start, end, pen, step_color);
	if (pen->step_green > 1 && d_fast)
		pen->step_green = (float)((unsigned char)(step_color >> 16)) / d_fast;
	if (pen->step_red > 1 && d_fast)
		pen->step_red = (float)((unsigned char)(step_color >> 8)) / d_fast;
}
