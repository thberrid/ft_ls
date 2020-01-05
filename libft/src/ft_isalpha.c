/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:54:01 by thberrid          #+#    #+#             */
/*   Updated: 2018/12/17 14:13:50 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islowcase(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

static int	ft_isupcase(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int			ft_isalpha(int c)
{
	if (ft_islowcase(c) || ft_isupcase(c))
		return (1);
	return (0);
}
