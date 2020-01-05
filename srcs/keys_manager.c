/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 01:30:39 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/02 01:30:41 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	switch_projection(t_window *w)
{
	if (w->proj_type == ORTHO)
		w->proj_type = PERSP;
	else
		w->proj_type = ORTHO;
}

void	img_set(t_window *w)
{
	img_setcolors(&w->px_coord, &w->obj_vertices);
	img_setalpha(&w->px_coord, &w->camera);
	img_setpositions(&w->px_coord, &w->proj_plan, w);
	img_centering(&w->px_coord, w);
}

int		send_modifications(int keycode, t_window *w)
{
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		if (!vertices_rotate(&w->obj_vertices, &angle_y,
			keycode == KEY_LEFT ? 0.25 : -0.25))
			return (0);
	if (keycode == KEY_TOP || keycode == KEY_BOTTOM)
		if (!vertices_scale(&w->obj_vertices,
		(keycode == KEY_BOTTOM) ? .75 : 1.25))
			return (0);
	return (1);
}

int		get_keypressed(unsigned int keycode, t_window *w)
{
	if (!ft_ischarset(keycode, KEYS_EXPECTED))
		return (0);
	matrix_free(&w->px_coord);
	if (keycode == KEY_ESC || keycode == KEY_Q)
		clean_w_and_exit(w);
	if (keycode == KEY_SPACE)
		switch_projection(w);
	if (!send_modifications(keycode, w))
		clean_w_and_exit(w);
	matrix_cpy(&w->camera, &w->obj_vertices);
	if (w->proj_type == ORTHO)
		matrix_apply(&w->proj_plan, &w->camera, 0, &ortho);
	else if (!render_persp(w))
		clean_w_and_exit(w);
	if (!matrix_init(&w->px_coord, &w->proj_plan, sizeof(t_pixel)))
		clean_w_and_exit(w);
	if (keycode == KEY_SPACE)
		if (!vertices_auto_adjust_scale(w, &w->proj_plan,
			(w->proj_type == PERSP) ? &perspective : &ortho))
			clean_w_and_exit(w);
	img_set(w);
	draw_obj(w);
	return (1);
}
