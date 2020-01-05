/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_persp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 05:39:44 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 21:01:08 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <math.h>

void		perspective(t_vertex *dest, t_vertex *src, float norm)
{
	int		focal;
	int		scale;

	focal = 20000;
	scale = ((src->z / (norm)) * focal);
	if (scale == 0)
		scale = 1;
	if (scale < 0)
		scale *= -1;
	dest->x = src->x;
	dest->y = src->y;
	dest->x = ceil(dest->x /= scale);
	dest->y = ceil(dest->y /= scale);
	dest->z = src->z;
}
