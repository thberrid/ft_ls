/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:27:27 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 23:00:12 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <math.h>

int		angle_y(t_matrix *matrix, double theta)
{
	t_vertex			*this;

	if (!malloc_matrix(matrix))
		return (0);
	this = &((t_vertex *)matrix->value[0])[0];
	this->x = (float)cos(theta);
	this->y = 0;
	this->z = (float)(-1 * sin(theta));
	this = &((t_vertex *)matrix->value[0])[1];
	this->x = 0;
	this->y = 1;
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[2];
	this->x = (float)sin(theta);
	this->y = 0;
	this->z = (float)cos(theta);
	return (1);
}

int		angle_x(t_matrix *matrix, double theta)
{
	t_vertex			*this;

	if (!malloc_matrix(matrix))
		return (0);
	this = &((t_vertex *)matrix->value[0])[0];
	this->x = 1;
	this->y = 0;
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[1];
	this->x = 0;
	this->y = (float)(cos(theta));
	this->z = (float)(sin(theta));
	this = &((t_vertex *)matrix->value[0])[2];
	this->x = 0;
	this->y = (float)(-1 * sin(theta));
	this->z = (float)(cos(theta));
	return (1);
}

int		angle_z(t_matrix *matrix, double theta)
{
	t_vertex			*this;

	if (!malloc_matrix(matrix))
		return (0);
	this = &((t_vertex *)matrix->value[0])[0];
	this->x = (float)cos(theta);
	this->y = (float)(sin(theta));
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[1];
	this->x = (float)(-1 * sin(theta));
	this->y = (float)(cos(theta));
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[2];
	this->x = 0;
	this->y = 0;
	this->z = 1;
	return (1);
}

void	matrix_transform(t_matrix *rot, t_vertex *vertices)
{
	t_vertex tmp;
	t_vertex *one;
	t_vertex *two;
	t_vertex *three;

	one = &((t_vertex *)rot->value[0])[0];
	two = &((t_vertex *)rot->value[0])[1];
	three = &((t_vertex *)rot->value[0])[2];
	tmp.x = (one->x * vertices->x) + (two->x * vertices->y)
		+ (three->x * vertices->z);
	tmp.y = (one->y * vertices->x) + (two->y * vertices->y)
		+ (three->y * vertices->z);
	tmp.z = (one->z * vertices->x) + (two->z * vertices->y)
		+ (three->z * vertices->z);
	vertices->x = tmp.x;
	vertices->y = tmp.y;
	vertices->z = tmp.z;
}

int		vertices_rotate(t_matrix *matrix,
		int (*set_angle)(t_matrix *, double), double rotation)
{
	unsigned int	i;
	unsigned int	j;
	t_matrix		rot;

	ft_bzero(&rot, sizeof(t_matrix));
	rot.row_len = 1;
	rot.column_len = 3;
	if (!set_angle(&rot, rotation))
		return (0);
	i = 0;
	while (i < matrix->row_len)
	{
		j = 0;
		while (j < matrix->column_len)
		{
			matrix_transform(&rot, &((t_vertex *)matrix->value[i])[j]);
			j += 1;
		}
		i += 1;
	}
	matrix_free(&rot);
	return (1);
}
