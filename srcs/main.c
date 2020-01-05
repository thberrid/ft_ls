/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 23:15:34 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
**	if y need to watch leaky leaks
**	system("leaks fdf");
*/

void	clean_w_and_exit(t_window *w)
{
	ft_putendl("exit called\n");
	matrix_free(&w->obj_vertices);
	mlx_destroy_image(w->mlx, w->img.id);
	mlx_destroy_window(w->mlx, w->ptr);
	exit(0);
}

void	print_usage(void)
{
	ft_putendl("\n< >      - rotations");
	ft_putendl("^ v      - zoom");
	ft_putendl("\n\"ok boomer\" - kevin\n");
}

void	window_init(t_window *w)
{
	ft_bzero(w, sizeof(t_window));
	w->width = 750;
	w->height = 750;
	w->proj_type = ORTHO;
	ft_strcpy(w->name, "ok boomer");
}

int		window_fill(t_window *w, char *file)
{
	if (!map_parse(&w->obj_vertices, file))
		return (0);
	if (!matrix_init(&w->proj_plan, &w->obj_vertices, sizeof(t_vertex))
		|| !w->obj_vertices.row_len)
		return (0);
	if (!matrix_init(&w->px_coord, &w->obj_vertices, sizeof(t_pixel)))
		return (0);
	if (!matrix_init(&w->camera, &w->obj_vertices, sizeof(t_vertex)))
		return (0);
	matrix_cpy(&w->camera, &w->obj_vertices);
	matrix_apply(&w->proj_plan, &w->camera, 0, &ortho);
	if (!vertices_auto_adjust_scale(w, &w->proj_plan, &ortho))
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	t_window		w;

	window_init(&w);
	if (ac == 2)
	{
		if (!window_fill(&w, av[1]))
			return (0);
		img_set(&w);
		print_usage();
		w.mlx = mlx_init();
		w.ptr = mlx_new_window(w.mlx, w.width, w.height, w.name);
		draw_obj(&w);
		mlx_key_hook(w.ptr, &get_keypressed, &w);
		mlx_loop(w.mlx);
	}
	return (0);
}
