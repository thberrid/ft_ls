/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_perspective.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 03:42:54 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/04 03:43:20 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <math.h>

int		set_persp(t_matrix *matrix)
{
	if (!malloc_matrix(matrix))
		return (0);
	return (1);
}

int		matrix_perspective(t_matrix *vertices)
{
	unsigned int		i;
	unsigned int		j;
	t_matrix			persp;

	ft_bzero(&persp, sizeof(t_matrix));
	persp.row_len = 1;
	persp.column_len = 3;
	if (!set_persp(&persp))
		return (0);
	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			matrix_transform(&persp, &((t_vertex *)vertices->value[i])[j]);
			j += 1;
		}
		i += 1;
	}
	matrix_free(&persp);
	return (1);
}
