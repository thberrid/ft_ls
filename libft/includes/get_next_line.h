/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:56:51 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 14:46:44 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 5

typedef struct	s_buf
{
	char	arr[BUFF_SIZE];
	int		len;
}				t_buf;

int				get_next_line(const int fd, char **line);

#endif
