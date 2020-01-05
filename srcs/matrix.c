/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:33:53 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 22:42:08 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	matrix_cpy(t_matrix *dest, t_matrix *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < src->row_len)
	{
		j = 0;
		while (j < src->column_len)
		{
			ft_memcpy(&((t_vertex *)dest->value[i])[j],
				&((t_vertex *)src->value[i])[j], sizeof(t_vertex) * 2);
			j += 1;
		}
		i += 1;
	}
}

/*
**	BROWSE A MATRIX
**	AND SET ITS VALUES FROM A SINGLE VECTOR
*/

void	matrix_set(t_matrix *vertices, t_vertex *vector,
				void (*f)(t_vertex *, t_vertex *))
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			f(&((t_vertex *)vertices->value[i])[j], vector);
			j += 1;
		}
		i += 1;
	}
}

/*
**	BROWSE A MATRIX
**	AND APPLY TRANFORMATIONS FROM ANOTHER SAME SIZED MATRIX
*/

void	matrix_apply(t_matrix *vertices, t_matrix *vectors,
			float norm, void (*f)(t_vertex *, t_vertex *, float))
{
	unsigned int	i;
	unsigned int	j;
	t_vertex		*vector;

	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			vector = &((t_vertex *)vectors->value[i])[j];
			f(&((t_vertex *)vertices->value[i])[j], vector, norm);
			j += 1;
		}
		i += 1;
	}
}

/*
** BROWSE A MATRIX
** AND RETURN VALUE DEPENDING A *FUNCTION
*/

float	matrix_get(t_matrix *vertices, float value, unsigned char dimension,
	float (*f)(float, t_vertex *, unsigned char))
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			value = f(value, &((t_vertex *)vertices->value[i])[j], dimension);
			j += 1;
		}
		i += 1;
	}
	return (value);
}

/*
**	CREATE AN EMPTY MATRIX
*/

int		matrix_init(t_matrix *new, t_matrix *src, unsigned char type)
{
	unsigned int	i;

	ft_bzero(new, sizeof(t_matrix));
	i = 0;
	new->row_len = src->row_len;
	new->column_len = src->column_len;
	if (!(new->value = ft_memalloc(sizeof(void *) * src->row_len)))
		return (0);
	while (i < src->row_len)
	{
		if (!(new->value[i] = ft_memalloc(type * src->column_len * 2)))
			return (0);
		i += 1;
	}
	return (1);
}
