/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:33:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 02:42:26 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	vertex_decrement(t_vertex *this, t_vertex *vector)
{
	this->x -= vector->x;
	this->y -= vector->y;
	this->z = (this->z * -1) + vector->z;
}

void	vertex_increment(t_vertex *this, t_vertex *vector)
{
	this->x += vector->x;
	this->y += vector->y;
	this->z += vector->z;
}

void	vertex_remove_null(t_matrix *vertices)
{
	t_vertex	min;

	min.x = matrix_get(vertices, FT_INTMAX, X, &get_min);
	min.y = matrix_get(vertices, FT_INTMAX, Y, &get_min);
	min.z = matrix_get(vertices, FT_INTMAX, Z, &get_min);
	min.x *= 2;
	min.y *= 2;
	min.z *= 2;
	if (min.x == 0)
		min.x = 1;
	if (min.y == 0)
		min.y = 1;
	if (min.z == 0)
		min.z = 1;
	if (min.x < 0)
		min.x *= -1;
	if (min.y < 0)
		min.y *= -1;
	if (min.z < 0)
		min.z *= -1;
	matrix_set(vertices, &min, &vertex_increment);
}
