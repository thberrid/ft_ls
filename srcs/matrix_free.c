/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 07:56:05 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 12:01:36 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				matrix_free(t_matrix *matrix)
{
	unsigned int	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < matrix->row_len)
	{
		ft_memdel((void **)&matrix->value[i]);
		i += 1;
	}
	ft_memdel((void **)&matrix->value);
}

int					malloc_matrix(t_matrix *matrix)
{
	unsigned int		i;

	if (!(matrix->value = ft_memalloc(sizeof(void *) * matrix->row_len)))
		return (0);
	i = 0;
	while (i < matrix->row_len)
	{
		if (!(matrix->value[i] = ft_memalloc(sizeof(t_vertex)
			* matrix->column_len)))
			return (0);
		i += 1;
	}
	return (1);
}
