/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_addrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 07:42:57 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 09:50:40 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
** PUT VERTICES IN THE LAST ROW
*/

static void			row_setvertex(t_matrix *matrix, char **raw, float y)
{
	unsigned int	i;
	unsigned int	rawlen;
	t_vertex		*this;

	this = ((t_vertex *)matrix->value[matrix->row_len - 1]);
	rawlen = raw_len(raw);
	i = 0;
	while (i < matrix->column_len && i < rawlen)
	{
		this[i].x = (float)i;
		this[i].y = (float)ft_atoi(raw[i]);
		this[i].z = y;
		i += 1;
	}
}

/*
** ADD AN EMPTY ROW TO THE MATRIX
*/

static int			matrix_extend(t_matrix *matrix)
{
	unsigned int	row_n;
	void			**new_value;

	new_value = ft_memalloc(sizeof(void *) * (matrix->row_len + 1));
	if (!new_value)
		return (0);
	row_n = 0;
	while (row_n < matrix->row_len)
	{
		new_value[row_n] = matrix->value[row_n];
		row_n += 1;
	}
	ft_memdel((void **)&matrix->value);
	matrix->row_len += 1;
	matrix->value = new_value;
	return (1);
}

int					matrix_addrow(t_matrix *matrix, char **raw, float y)
{
	void			*new_row;

	if (!matrix_extend(matrix))
		return (0);
	if (!matrix->column_len)
		matrix->column_len = raw_len(raw);
	if (!(new_row = ft_memalloc(matrix->column_len * matrix->type)))
		return (0);
	matrix->value[matrix->row_len - 1] = (void *)new_row;
	row_setvertex(matrix, raw, y);
	return (1);
}
