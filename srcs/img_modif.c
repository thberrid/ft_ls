/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_modif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 04:07:43 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/02 04:07:46 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	set_minmax(t_vertex *min, t_vertex *max, t_matrix *matrix)
{
	min->y = matrix_get(matrix, FT_INTMAX, Y, &get_min);
	max->y = matrix_get(matrix, FT_INTMIN, Y, &get_max);
	min->z = matrix_get(matrix, FT_INTMAX, Z, &get_min);
	max->z = matrix_get(matrix, FT_INTMIN, Z, &get_max);
}

void	img_centering(t_matrix *img, t_window *w)
{
	unsigned int	y;
	unsigned int	x;
	int				shift_x;
	int				shift_y;
	t_pixel			*px;

	shift_x = int_minmax(img,
		FT_INTMIN, X, &is_sup) - ((w->width) / 2) - (int_range(img, X) / 2);
	shift_y = int_minmax(img,
		FT_INTMIN, Y, &is_sup) - ((w->height) / 2) - (int_range(img, Y) / 2);
	y = 0;
	while (y < img->row_len)
	{
		x = 0;
		while (x < img->column_len)
		{
			px = &((t_pixel *)img->value[y])[x];
			px->x -= shift_x;
			px->y -= shift_y;
			x += 1;
		}
		y += 1;
	}
}

void	apply_scale(t_matrix *img, t_matrix *plan, t_window *w, float scaler)
{
	unsigned int	y;
	unsigned int	x;
	t_pixel			*px;
	t_vertex		*this_vertex;
	t_vertex		*this_y;

	y = 0;
	while (y < img->row_len)
	{
		x = 0;
		while (x < img->column_len)
		{
			px = &((t_pixel *)img->value[y])[x];
			this_vertex = &((t_vertex *)plan->value[y])[x];
			this_y = &((t_vertex *)w->obj_vertices.value[y])[x];
			px->x = (unsigned int)(this_vertex->x * scaler);
			px->y = w->height - ((unsigned int)(this_vertex->y * scaler));
			x += 1;
		}
		y += 1;
	}
}
