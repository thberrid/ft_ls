/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 03:48:01 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 09:46:14 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fcntl.h>

float		get_min(float value, t_vertex *new_vertex, unsigned char dimension)
{
	float new_value;

	new_value = new_vertex->x;
	if (dimension == Y)
		new_value = new_vertex->y;
	if (dimension == Z)
		new_value = new_vertex->z;
	if (new_value < value)
		return (new_value);
	return (value);
}

float		get_max(float value, t_vertex *new_vertex, unsigned char dimension)
{
	float new_value;

	new_value = new_vertex->x;
	if (dimension == Y)
		new_value = new_vertex->y;
	if (dimension == Z)
		new_value = new_vertex->z;
	if (new_value > value)
		return (new_value);
	return (value);
}

static void	map_reindex_z(t_matrix *vertices)
{
	t_vertex	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = vertices->row_len;
	matrix_set(vertices, &vector, &vertex_decrement);
}

/*
**	CONVERT FILE INTO MATRIX OF VERTICES
*/

int			map_parse(t_matrix *vertices, char *path)
{
	int				fd;
	int				retrn;
	char			*line;
	char			**raw;
	unsigned int	line_n;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	line = NULL;
	line_n = 0;
	ft_bzero(vertices, sizeof(t_matrix));
	vertices->type = sizeof(t_vertex);
	while ((retrn = get_next_line(fd, &line)))
	{
		if (retrn < 0 || !(raw = ft_strsplitspaces(line)))
			return (0);
		if (raw_len(raw))
			if (!matrix_addrow(vertices, raw, (float)line_n))
				return (0);
		ft_strdel(&line);
		raw_free(raw);
		line_n += 1;
	}
	map_reindex_z(vertices);
	return (1);
}
