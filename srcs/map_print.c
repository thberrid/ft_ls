/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:35:36 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 08:48:41 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static float	get_padding(float value, t_vertex *new_vertex,
	unsigned char dimension)
{
	int		padding;
	float	new_value;

	new_value = new_vertex->x;
	if (dimension == Y)
		new_value = new_vertex->y;
	if (dimension == Z)
		new_value = new_vertex->z;
	padding = ft_intlen((int)new_value);
	if (padding + 1 > value)
		return ((float)(padding + 1));
	return (value);
}

static void		print_y(t_vertex *vertex, t_vertex *padding)
{
	int		intlen;

	ft_putstr("x: ");
	ft_putnbr((int)vertex->x);
	ft_putchar(' ');
	ft_putstr("y: ");
	ft_putnbr((int)vertex->y);
	ft_putchar(' ');
	ft_putstr("z: ");
	ft_putnbr((int)vertex->z);
	ft_putchar('\n');
	ft_putchar('\n');
	intlen = (int)padding->y;
	intlen -= ft_intlen((int)vertex->y);
}

void			map_print(t_matrix *vertices)
{
	t_vertex	padding;

	ft_bzero(&padding, sizeof(t_vertex));
	padding.y = matrix_get(vertices, 0, Y, &get_padding);
	padding.z = vertices->column_len;
	matrix_set(vertices, &padding, print_y);
}
