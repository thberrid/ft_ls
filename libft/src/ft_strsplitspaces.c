/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitspaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:23:20 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/02 05:26:29 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_countword(char const *s)
{
	size_t	count_word;
	int		prev_isspace;

	count_word = 0;
	prev_isspace = 1;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			if (prev_isspace)
				count_word += 1;
			prev_isspace = 0;
		}
		else
			prev_isspace = 1;
		s += 1;
	}
	return (count_word);
}

static int		ft_freearray(char **array, int n)
{
	while (n > 0)
	{
		n -= 1;
		ft_strdel(&array[n]);
	}
	return (0);
}

static int		ft_fillstrsplt(char **array, char const *s, size_t len)
{
	size_t	size;
	size_t	i;

	i = 0;
	while (i < len)
	{
		size = 0;
		while (ft_isspace(*s))
			s += 1;
		while (s[size] && !ft_isspace(s[size]))
			size += 1;
		array[i] = ft_strsub(s, 0, size);
		if (!array)
			return (ft_freearray(array, i));
		s += size;
		i += 1;
	}
	return (1);
}

char			**ft_strsplitspaces(char const *s)
{
	char	**new_array;
	size_t	count_word;

	count_word = ft_countword(s);
	new_array = (char **)ft_memalloc(sizeof(char *) * (count_word + 1));
	if (new_array)
	{
		new_array[count_word] = 0;
		if (!ft_fillstrsplt(new_array, s, count_word))
			ft_memdel((void **)&new_array);
	}
	return (new_array);
}
