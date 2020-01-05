/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 18:23:12 by thberrid          #+#    #+#             */
/*   Updated: 2019/05/16 18:23:35 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstgetn(t_list *list, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		i += 1;
		list = list->next;
		if (!list)
			return (NULL);
	}
	return (list);
}
