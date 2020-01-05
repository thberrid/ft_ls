/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 08:31:18 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 08:36:36 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

float			get_range(t_matrix *plan, unsigned char dimension)
{
	float	min;
	float	max;

	min = matrix_get(plan, FT_INTMAX, dimension, &get_min);
	max = matrix_get(plan, FT_INTMIN, dimension, &get_max);
	return (max - min);
}

int				get_dimension(int dimension, t_pixel *px)
{
	if (dimension == X)
		return (px->x);
	return (px->y);
}

unsigned char	get_alt_color(float y, float max)
{
	unsigned char color;

	color = (unsigned char)((y * 255) / max);
	return (color);
}

unsigned char	get_alt_alpha(float y, float max)
{
	unsigned char alpha;

	alpha = (unsigned char)((y * 220) / max);
	return (alpha);
}
