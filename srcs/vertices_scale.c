/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 04:16:19 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/02 04:16:21 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		set_scale(t_matrix *matrix, float coef)
{
	t_vertex		*this;

	if (!malloc_matrix(matrix))
		return (0);
	this = &((t_vertex *)matrix->value[0])[0];
	this->x = coef;
	this->y = 0;
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[1];
	this->x = 0;
	this->y = coef;
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[2];
	this->x = 0;
	this->y = 0;
	this->z = coef;
	return (1);
}

int		vertices_scale(t_matrix *vertices, float coef)
{
	unsigned int		i;
	unsigned int		j;
	t_matrix			scale;

	ft_bzero(&scale, sizeof(t_matrix));
	scale.row_len = 1;
	scale.column_len = 3;
	if (!set_scale(&scale, coef))
		return (0);
	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			matrix_transform(&scale, &((t_vertex *)vertices->value[i])[j]);
			j += 1;
		}
		i += 1;
	}
	matrix_free(&scale);
	return (1);
}
