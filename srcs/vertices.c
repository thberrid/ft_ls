/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 03:33:34 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:04 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		is_smaller(float x_range, float y_range, t_window *w)
{
	if (y_range < w->height * 0.65 && x_range < w->width * 0.65)
		return (1);
	return (0);
}

int		is_bigger(float x_range, float y_range, t_window *w)
{
	if (y_range > w->height * 0.65 || x_range > w->width * 0.65)
		return (1);
	return (0);
}

int		vertices_compare(t_window *w, t_matrix *plan,
	int (*compare)(float, float, t_window *))
{
	float	x_max;
	float	x_min;
	float	y_max;
	float	y_min;

	x_min = matrix_get(plan, FT_INTMAX, X, &get_min);
	x_max = matrix_get(plan, FT_INTMIN, X, &get_max);
	y_min = matrix_get(plan, FT_INTMAX, Y, &get_min);
	y_max = matrix_get(plan, FT_INTMIN, Y, &get_max);
	return (compare(x_max - x_min, y_max - y_min, w));
}

int		render_persp(t_window *w)
{
	matrix_cpy(&w->camera, &w->obj_vertices);
	if (!vertices_rotate(&w->camera, &angle_x, -1.25))
		return (0);
	vertex_remove_null(&w->camera);
	matrix_apply(&w->proj_plan, &w->camera,
		matrix_get(&w->camera, FT_INTMIN, Z, &get_max), &perspective);
	return (1);
}

int		vertices_auto_adjust_scale(t_window *w, t_matrix *plan,
		void (*proj)(t_vertex *, t_vertex *, float))
{
	float	coef;
	int		(*f)(float, float, t_window *);

	coef = 2;
	f = &is_bigger;
	if (vertices_compare(w, plan, is_bigger))
	{
		coef = 0.5;
		f = &is_smaller;
	}
	while (!vertices_compare(w, plan, f))
	{
		if (!vertices_scale(&w->obj_vertices, coef))
			return (0);
		matrix_cpy(&w->camera, &w->obj_vertices);
		if (proj == &perspective)
		{
			if (!render_persp(w))
				return (0);
		}
		else
			matrix_apply(plan, &w->camera, 0, proj);
	}
	return (1);
}
