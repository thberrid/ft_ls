/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:22:22 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 06:39:40 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void			bresen_set_delta(t_pixel *delta, t_pixel *start, t_pixel *end)
{
	delta->x = end->x - start->x;
	delta->y = end->y - start->y;
	if (delta->x < 0)
		delta->x *= -1;
	if (delta->y < 0)
		delta->y *= -1;
}

unsigned int	bresen_set_deltafast(t_pixel *start, t_pixel *end)
{
	t_pixel			delta;
	unsigned int	delta_fast;

	bresen_set_delta(&delta, start, end);
	delta_fast = delta.x > delta.y ? delta.x : delta.y;
	return (delta_fast);
}

float			bresen_update_error(float error, t_pixel *start, t_pixel *end,
	t_pixel *pen)
{
	unsigned int	delta_slow;
	t_pixel			delta;
	t_pixel			step;

	bresen_set_delta(&delta, start, end);
	delta_slow = delta.x < delta.y ? delta.x : delta.y;
	step.x = end->x > start->x ? 1 : -1;
	step.y = end->y > start->y ? 1 : -1;
	error -= delta_slow;
	if (error <= 0)
	{
		if (delta.x > delta.y)
			pen->y += step.y;
		else
			pen->x += step.x;
		error += (delta.x > delta.y ? delta.x : delta.y);
	}
	if (delta.x <= delta.y)
		pen->y += step.y;
	else
		pen->x += step.x;
	return (error);
}
