/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:42:02 by thberrid          #+#    #+#             */
/*   Updated: 2019/05/31 23:16:30 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <get_next_line.h>

static int	clear_remaining(char **remaining, char **line)
{
	char	*position;

	if (*remaining && (position = ft_strchr(*remaining, '\n')))
	{
		*position = '\0';
		*line = ft_strdup(*remaining);
		if (!*line)
			return (-1);
		if (*(position + 1))
			ft_strcpy(*remaining, position + 1);
		else
			ft_strdel(remaining);
		return (1);
	}
	if (!(*line = ft_strdup(*remaining)))
		return (-1);
	ft_strdel(remaining);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char			buffer[BUFF_SIZE + 1];
	static char		*remaining = NULL;
	char			*tmp;
	int				retrn;

	while ((retrn = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[retrn] = '\0';
		if (ft_memchr(buffer, 0, retrn) || !(tmp = ft_strdup(remaining)))
			return (-1);
		ft_strdel(&remaining);
		if (!(remaining = ft_strjoin(tmp, buffer)))
			return (-1);
		ft_strdel(&tmp);
		if (ft_strchr(remaining, '\n'))
			break ;
	}
	if (remaining)
		return (clear_remaining(&remaining, line));
	return (retrn);
}
