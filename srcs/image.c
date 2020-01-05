/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:52:05 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 08:35:13 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		is_inf(int a, t_pixel *px, int dimension)
{
	int	b;

	b = get_dimension(dimension, px);
	if (a < b)
		return (a);
	return (b);
}

int		is_sup(int a, t_pixel *px, int dimension)
{
	int	b;

	b = get_dimension(dimension, px);
	if (a > b)
		return (a);
	return (b);
}

int		int_minmax(t_matrix *matrix, int def_val, int dimension,
	int (*f)(int, t_pixel *, int))
{
	unsigned int		i;
	unsigned int		j;
	int					extrem;

	i = 0;
	extrem = def_val;
	while (i < matrix->row_len)
	{
		j = 0;
		while (j < matrix->column_len)
		{
			extrem = f(extrem, &((t_pixel *)matrix->value[i])[j], dimension);
			j += 1;
		}
		i += 1;
	}
	return (extrem);
}

int		int_range(t_matrix *matrix, int dimension)
{
	int min;
	int max;

	min = int_minmax(matrix, FT_INTMAX, dimension, &is_inf);
	max = int_minmax(matrix, FT_INTMIN, dimension, &is_sup);
	return (max - min);
}

void	img_scaling(t_matrix *img, t_matrix *plan, t_window *w)
{
	float		ratio_img;
	float		ratio_w;
	float		scaler;

	ratio_img = get_range(plan, X) / get_range(plan, Y);
	ratio_w = (w->width - 100) / (w->height - 100);
	if (ratio_img > ratio_w)
		scaler = (w->width - 100) / get_range(plan, X);
	else
		scaler = (w->height - 100) / get_range(plan, Y);
	apply_scale(img, plan, w, scaler);
}
