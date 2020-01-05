/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 08:29:34 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 22:31:47 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	color_set(t_vertex *min, t_vertex *max, t_pixel *px, t_vertex *this_y)
{
	if (this_y->y > 0)
		color_remove(&px->color, get_alt_color(this_y->y + 1, max->y + 1), RED);
	if (this_y->y < 0)
		color_remove(&px->color,
			get_alt_color(this_y->y + 1, min->y + 1), GREEN);
}

void	img_setcolors(t_matrix *img, t_matrix *obj)
{
	t_vertex		min;
	t_vertex		max;
	t_pixel			index;
	t_pixel			*px;
	t_vertex		*this_vertex;

	set_minmax(&min, &max, obj);
	index.y = 0;
	while ((unsigned int)index.y < img->row_len)
	{
		index.x = 0;
		while ((unsigned int)index.x < img->column_len)
		{
			px = &((t_pixel *)img->value[index.y])[index.x];
			this_vertex = &((t_vertex *)obj->value[index.y])[index.x];
			color_setwhite(&px->color);
			color_set(&min, &max, px, this_vertex);
			index.x += 1;
		}
		index.y += 1;
	}
}

void	img_setalpha(t_matrix *img, t_matrix *obj)
{
	float			min;
	float			max;
	t_pixel			index;
	t_vertex		*this_vertex;

	min = matrix_get(obj, FT_INTMAX, Z, &get_min);
	max = matrix_get(obj, FT_INTMIN, Z, &get_max);
	if (min < 0)
		min *= -1;
	if (max < 0)
		max *= -1;
	index.y = 0;
	while ((unsigned int)index.y < img->row_len)
	{
		index.x = 0;
		while ((unsigned int)index.x < img->column_len)
		{
			this_vertex = &((t_vertex *)obj->value[index.y])[index.x];
			color_add(&(&((t_pixel *)img->value[index.y])[index.x])->color,
			get_alt_alpha(this_vertex->z + min, max + min), ALPHA);
			index.x += 1;
		}
		index.y += 1;
	}
}

void	img_setpositions(t_matrix *img, t_matrix *plan, t_window *w)
{
	t_pixel			index;
	t_pixel			*px;
	t_vertex		*this_vertex;

	index.y = 0;
	while ((unsigned int)index.y < img->row_len)
	{
		index.x = 0;
		while ((unsigned int)index.x < img->column_len)
		{
			px = &((t_pixel *)img->value[index.y])[index.x];
			this_vertex = &((t_vertex *)plan->value[index.y])[index.x];
			px->x = (unsigned int)(this_vertex->x);
			px->y = w->height - ((unsigned int)(this_vertex->y));
			index.x += 1;
		}
		index.y += 1;
	}
}
